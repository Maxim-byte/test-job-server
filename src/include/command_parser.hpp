#pragma once

#include <string>
#include <vector>

class command_parser {
public:
    static std::string process_set_state(std::vector<std::string> &tokens);

    static std::string process_set_color(std::vector<std::string> &tokens);

    static std::string process_set_rate(std::vector<std::string> &tokens);

    static std::string process_get_state(std::vector<std::string> &tokens);

    static std::string process_get_color(std::vector<std::string> &tokens);

    static std::string process_get_rate(std::vector<std::string> &tokens);

};
