cmake_minimum_required(VERSION 3.27)

project(jsonparser)

add_library(parser_lib JsonParser.cpp JsonParser.h)

add_executable(json_parser main.cpp)

target_link_libraries(json_parser PRIVATE parser_lib)