#include "../include/command_parser.hpp"

#include <spdlog/spdlog.h>
#include <boost/algorithm/string.hpp>

#include "../include/config.hpp"
#include "../include/light.hpp"

namespace {
    const std::string ok = "OK";
    const std::string failed = "FAILED";
}

std::string command_parser::process_set_state(std::vector<std::string> &tokens) {
    if (tokens.size() != 2) {
        spdlog::get(config::instance().get_logger_name())->info("set-state invalid number of tokens");
        return failed;
    }
    return light::instance().switch_state(tokens[1]) ? ok : failed;
}

std::string command_parser::process_set_color(std::vector<std::string> &tokens) {
    if (tokens.size() != 2) {
        spdlog::get(config::instance().get_logger_name())->info("set-color invalid number of tokens");
        return failed;
    }
    return light::instance().switch_color(tokens[1]) ? ok : failed;
}

std::string command_parser::process_set_rate(std::vector<std::string> &tokens) {
    if (tokens.size() != 2) {
        spdlog::get(config::instance().get_logger_name())->info("set-rate invalid number of tokens");
        return failed;
    }
    return light::instance().switch_rate(tokens[1]) ? ok : failed;
}

std::string command_parser::process_get_state(std::vector<std::string> &tokens) {
    if (tokens.size() != 1) {
        spdlog::get(config::instance().get_logger_name())->info("get-state invalid number of tokens");
        return failed;
    }
    return ok + " " + light::instance().get_current_state();
}

std::string command_parser::process_get_color(std::vector<std::string> &tokens) {
    if (tokens.size() != 1) {
        spdlog::get(config::instance().get_logger_name())->info("get-color invalid number of tokens");
        return failed;
    }
    return ok + " " + light::instance().get_current_color();
}

std::string command_parser::process_get_rate(std::vector<std::string> &tokens) {
    if (tokens.size() != 1) {
        spdlog::get(config::instance().get_logger_name())->info("get-rate invalid number of tokens");
        return failed;
    }
    return ok + " " + light::instance().get_current_rate();
}
