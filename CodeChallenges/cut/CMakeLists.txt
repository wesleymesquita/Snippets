cmake_minimum_required(VERSION 3.27)

project(Cut)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cut_lib Cut.cpp Cut.h)

#Tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
add_executable(cut_test Tests.cpp)
target_link_libraries(cut_test GTest::gtest_main cut_lib)
gtest_discover_tests(cut_test)

#Main
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} cut_lib)

