#pragma once

#include <string>

struct network_config {
    std::string host;
    std::uint16_t port;
    std::uint8_t timeout_socket;
};
