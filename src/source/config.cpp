#include "../include/config.hpp"

#include <fstream>
#include <cassert>
#include <iostream>

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

config::config() {
    std::ifstream config_stream(std::string{path_to_config});
    assert(config_stream.is_open());

    //parse network config
    try {
        nlohmann::json config = nlohmann::json::parse(config_stream);

        network_.host = config["network_config"]["host"].get<std::string>();
        boost::system::error_code ec;
        boost::asio::ip::make_address_v4(network_.host, ec);
        assert(!ec && "Rpc host is inconvertible to ipV4!");

        network_.port = config["network_config"]["port"].get<std::uint16_t>();
        assert(network_.port != 0);

        network_.timeout_socket = config["network_config"]["timeout_socket_s"].get<std::uint8_t>();
        assert(network_.timeout_socket != 0);

        logger_name_ = config["logger_name"].get<std::string>();
        assert(!logger_name_.empty());
    } catch (const std::exception &ex) {
        std::cerr << "Can't init config_manager: " << ex.what() << std::endl;
        std::exit(1);
    }
}

const network_config &config::get_network_config() const {
    return network_;
}

const std::string &config::get_logger_name() const {
    return logger_name_;
}
