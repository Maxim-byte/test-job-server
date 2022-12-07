#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

namespace utility::light {
    enum class state : std::uint8_t {
        ON,
        OFF
    };
    enum class color : std::uint8_t {
        RED,
        GREEN,
        BLUE
    };

    const inline std::unordered_map<std::string, state> state_converter_s{
            {"ON",  state::ON},
            {"OFF", state::OFF}
    };
    const inline std::unordered_map<state, std::string> state_converter_e{
            {state::ON,  "ON"},
            {state::OFF, "OFF"}
    };

    const inline std::unordered_map<std::string, color> color_converter_s{
            {"RED",   color::RED},
            {"GREEN", color::GREEN},
            {"BLUE",  color::BLUE}
    };
    const inline std::unordered_map<color, std::string> color_converter_e{
            {color::RED,   "RED"},
            {color::GREEN, "GREEN"},
            {color::BLUE,  "BLUE"}
    };
}