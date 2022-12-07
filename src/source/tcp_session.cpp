#include "../include/tcp_session.hpp"

#include <chrono>
#include <iostream>

#include <spdlog/spdlog.h>
#include <boost/algorithm/string.hpp>

#include "../include/api.hpp"
#include "../include/config.hpp"

namespace {
    const std::uint8_t time_expires_socket_in_seconds = config::instance().get_network_config().timeout_socket * 5;
}

session::session(boost::asio::ip::tcp::socket &&socket) :
        stream_(std::move(socket)) {}

void session::start_read() {
    stream_.expires_after(std::chrono::seconds(time_expires_socket_in_seconds));
    boost::asio::async_read_until(stream_, buffer_, "\n", boost::beast::bind_front_handler(&session::read_callback, shared_from_this()));
}

void session::read_callback(boost::beast::error_code ec, std::size_t /*bytes_transferred*/) {
    if (ec == boost::beast::error::timeout) {
        spdlog::get(config::instance().get_logger_name())->info("timeout while reading");
        close_stream();
        return;
    }
    if (ec) {
        spdlog::get(config::instance().get_logger_name())->warn("error occurred while reading request: " + ec.what());
        close_stream();
    } else {
        std::string command((std::istreambuf_iterator<char>(&buffer_)), std::istreambuf_iterator<char>());
        auto tokens = parse_command_into_token(command);
        std::string response;
        if (auto it = api::table::api_handlers.find(tokens[0]); it != api::table::api_handlers.end()) {
            response = it->second(tokens);
            response += "\n";
        } else {
            spdlog::get(config::instance().get_logger_name())->info("invalid command: " + command);
            response = "FAILED\n";
        }
        boost::asio::async_write(stream_, boost::asio::buffer(response),
                                 boost::beast::bind_front_handler(&session::write_callback, shared_from_this()));
    }
}

void session::write_callback(boost::beast::error_code ec, std::size_t) {
    if (ec) {
        spdlog::get(config::instance().get_logger_name())->warn("error occurred while writing request: " + ec.what());
        return close_stream();
    }
    start_read();
}

void session::close_stream() {
    boost::beast::error_code ec;
    if (stream_.socket().is_open()) {
        stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
    }
    if (ec) {
        spdlog::get(config::instance().get_logger_name())->warn("error occurred while closing tcp-session: " + ec.what());
    }
}

std::vector<std::string> session::parse_command_into_token(const std::string &command) {
    std::vector<std::string> command_token;
    boost::split(command_token, command, boost::is_any_of(" "));
    boost::trim(command_token.back());
    return std::move(command_token);
}
