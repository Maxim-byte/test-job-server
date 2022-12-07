#include "../include/light.hpp"

#include <regex>

#include <spdlog/spdlog.h>
#include <boost/algorithm/string.hpp>

#include "../include/config.hpp"

light::light() :
        current_state_(utility::light::state::ON),
        current_color_(utility::light::color::GREEN),
        current_rate_{0, 5} {}

bool light::switch_state(std::string &new_state) {
    if (auto it = utility::light::state_converter_s.find(new_state); it != utility::light::state_converter_s.end()) {
        current_state_ = it->second;
        spdlog::get(config::instance().get_logger_name())->info("state successful changed to: " + new_state);
        return true;
    }
    spdlog::get(config::instance().get_logger_name())->info("error occurred while changing state to: " + new_state);
    return false;
}

bool light::switch_color(std::string &new_color) {
    if (auto it = utility::light::color_converter_s.find(new_color); it != utility::light::color_converter_s.end()) {
        current_color_ = it->second;
        spdlog::get(config::instance().get_logger_name())->info("color successful changed to: " + new_color);
        return true;
    }
    spdlog::get(config::instance().get_logger_name())->info("error occurred while changing color to: " + new_color);
    return false;
}

bool light::switch_rate(std::string &new_rate) {
    static const std::regex regex("[0-9]*\\.\\.[0-9]*");
    if (std::regex_match(new_rate, regex)) {
        current_rate_ = new_rate;
        spdlog::get(config::instance().get_logger_name())->info("rate successful changed to: " + new_rate);
        return true;
    }
    spdlog::get(config::instance().get_logger_name())->info("error occurred while changing rate to: " + new_rate);
    return false;
}

std::string light::get_current_state() {
    spdlog::get(config::instance().get_logger_name())->info("state successful get");
    return utility::light::state_converter_e.find(current_state_)->second;
}

std::string light::get_current_color() {
    spdlog::get(config::instance().get_logger_name())->info("color successful get");
    return utility::light::color_converter_e.find(current_color_)->second;
}

std::string light::get_current_rate() {
    spdlog::get(config::instance().get_logger_name())->info("rate successful get");
    return current_rate_;
}
