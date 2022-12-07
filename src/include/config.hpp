#pragma once

#include <filesystem>

#include "config_structs.hpp"

class config {
public:
    constexpr static std::string_view path_to_config = "/home/maxim/CLionProjects/test_job_server/config/common_config.json";

    static config &instance() {
        static config config;
        return config;
    }

    [[nodiscard]] const network_config &get_network_config() const;

    [[nodiscard]] const std::string &get_logger_name() const;

private:
    config();

    network_config network_;
    std::string logger_name_;
};

