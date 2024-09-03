# ref https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/

# for libGL error: No matching fbConfigs or visuals found ssh
# https://github.com/XQuartz/XQuartz/issues/231#issuecomment-990871765

# enable 3d support if running on VMWare player

#grid image source
#https://upload.wikimedia.org/wikipedia/commons/6/63/Pixel_grid_4000x2000.svg

cmake_minimum_required(VERSION 3.27)

project(RandomWalk)


#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_library(random_walk_lib RandomWalk.cpp RandomWalk.h)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} random_walk_lib)

#https://stackoverflow.com/questions/23850472/how-to-use-sdl2-and-sdl-image-with-cmake
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})