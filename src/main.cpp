#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "include/config.hpp"
#include "include/server.hpp"

int main() {
    //init config
    auto &config = config::instance();

    boost::asio::io_context io;

    auto console_logger = spdlog::stdout_color_mt(config.get_logger_name());
    console_logger->set_error_handler([](const std::string &string) {
        std::cerr << string << std::endl;
    });

    //correct closing by signal
    boost::asio::signal_set signals(io, SIGTERM);
    signals.async_wait([&](const boost::system::error_code &error, int signal_number) {
        console_logger->info("shutdown server: sigterm signal...");
        io.stop();
    });

    //setup rest-http server
    std::shared_ptr<server> http_server;
    try {
        http_server = std::make_shared<server>(
                io,
                boost::asio::ip::tcp::endpoint
                        {
                                boost::asio::ip::make_address_v4(config.get_network_config().host),
                                config.get_network_config().port
                        }
        );
        http_server->start();
        console_logger->info("server started...");
    } catch (const std::exception &ex) {
        console_logger->critical(std::string("fatal error while starting server: ") + ex.what());
        return -1;
    }
    io.run();
    return 0;
}
