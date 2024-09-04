//
// Created by wesley on 9/3/24.
//

#include <iostream>
#include <random>
#include <vector>

#include <SDL.h>
// for image, remember to sudo apt-get install libsdl2-image-dev
#include <SDL_image.h>
#include "RandomWalk.h"

RandomWalk::RandomWalk(size_t iteractions) : interactions{iteractions} {
    mt = std::mt19937(rd());
    dist_width = std::uniform_int_distribution<int>(0, WIDTH);
    dist_height = std::uniform_int_distribution<int>(0, HEIGHT);
}


bool RandomWalk::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error on SDL_Init : " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Random Walk Simulator",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Error on SDL_CreateWindow : " << SDL_GetError() << std::endl;
        return false;
    }

//    screen_surface = SDL_GetWindowSurface(window);
//    if (screen_surface == nullptr) {
//        std::cerr << "Error on SDL_GetWindowSurface : " << SDL_GetError() << std::endl;
//        return false;
//    }

    //https://stackoverflow.com/questions/21007329/what-is-an-sdl-renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr) {
        std::cerr << "Error on SDL_CreateRenderer : " << SDL_GetError() << std::endl;
        return false;
    }

    //_load_grid();

    return true;
}


bool RandomWalk::start() {
    SDL_Event event;
    SDL_Point *points;
    int n_points = this->interactions;
    int i_point = 0;
    points = new SDL_Point[n_points];

    size_t n_interactions{0};
    points[i_point].x = _get_random_width();
    points[i_point].y = _get_random_height();
    i_point++;

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_UP) {
                points[i_point].x = _get_random_width();
                points[i_point].y = _get_random_height();
                i_point++;

                if (SDL_RenderDrawLines(renderer, points, i_point) == 0) {
                    std::cout << "Presenting render " << std::endl;
                    SDL_RenderPresent(renderer);
                    n_interactions++;
                } else {
                    std::cerr << "Error to draw line " << SDL_GetError() << std::endl;
                }
            }
            if (i_point >= this->interactions) {
                break;
            }
        }
    }
    delete [] points;
    return true;
}

bool RandomWalk::stop() {
    return true;
}

bool RandomWalk::destroy() {
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(grid_texture);
    SDL_Quit();
    return true;
}


bool RandomWalk::_load_grid() {

    //https://gamedev.stackexchange.com/questions/59078/sdl-function-for-loading-pngs
    IMG_Init(IMG_INIT_PNG);
    grid_texture = IMG_LoadTexture(renderer, "../images/grid.png");
    SDL_RenderCopy(renderer, grid_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    return true;
}

int RandomWalk::_get_random_width() {
    return dist_width(mt);
}

int RandomWalk::_get_random_height() {
    return dist_height(mt);
}
