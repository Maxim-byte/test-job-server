#pragma once

#include <string>
#include <unordered_map>

#include "light_utility.hpp"

class light {
public:
    static light &instance() {
        static light config_manager;
        return config_manager;
    }

    [[nodiscard]] bool switch_state(std::string &new_state);

    [[nodiscard]] bool switch_color(std::string &new_color);

    [[nodiscard]] bool switch_rate(std::string &new_rate);

    [[nodiscard]] std::string get_current_state();

    [[nodiscard]] std::string get_current_color();

    [[nodiscard]] std::string get_current_rate();

private:
    utility::light::state current_state_;
    utility::light::color current_color_;
    std::string current_rate_;

    light();
};

