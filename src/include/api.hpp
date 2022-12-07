#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "command_parser.hpp"

namespace api::table {
    inline const std::unordered_map<std::string, std::function<std::string(std::vector<std::string> &)>> api_handlers{
            {"set-led-state", &command_parser::process_set_state},
            {"set-led-color", &command_parser::process_set_color},
            {"set-led-rate",  &command_parser::process_set_rate},
            {"get-led-state", &command_parser::process_get_state},
            {"get-led-color", &command_parser::process_get_color},
            {"get-led-rate",  &command_parser::process_get_rate},
    };
}