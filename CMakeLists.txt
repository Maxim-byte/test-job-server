cmake_minimum_required(VERSION 3.24)
project(test_job_server)

set(CMAKE_CXX_STANDARD 17)
set(path_to_conan_directory "./conan")

include(${path_to_conan_directory}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(test_job_server
        src/main.cpp
        src/source/command_parser.cpp
        src/source/server.cpp
        src/source/tcp_session.cpp
        src/source/config.cpp
        src/source/light.cpp
        src/include/config_structs.hpp
        src/include/light.hpp
        src/include/tcp_session.hpp
        src/include/server.hpp
        src/include/config.hpp
        src/include/config_structs.hpp
        src/include/light_utility.hpp src/include/api.hpp)

target_link_libraries(test_job_server ${CONAN_LIBS})
