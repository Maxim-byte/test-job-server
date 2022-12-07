#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

class session : public std::enable_shared_from_this<session> {
public:
    explicit session(boost::asio::ip::tcp::socket &&socket);

    void start_read();

private:
    boost::beast::tcp_stream stream_;
    boost::asio::streambuf buffer_;

private:
    void read_callback(boost::beast::error_code ec, std::size_t /*bytes_transferred*/);

    void write_callback(boost::beast::error_code ec, std::size_t /*bytes_transferred*/);

    void close_stream();

    static std::vector<std::string> parse_command_into_token(const std::string &command);

};
