cmake_minimum_required(VERSION 3.27)

project(jsonparser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(parser_lib JsonParser.cpp JsonParser.h)

add_executable(json_parser main.cpp)
add_executable(parser_test Tests.cpp)

target_link_libraries(json_parser PRIVATE parser_lib)
target_link_libraries(parser_test GTest::gtest_main parser_lib)
include_directories("build/_deps/googletest-src/googletest/include")

include(GoogleTest)
gtest_discover_tests(parser_test)
