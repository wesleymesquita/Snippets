//
// Created by wesley on 9/3/24.
//

#ifndef SDL2HELLO_RANDOMWALK_H
#define SDL2HELLO_RANDOMWALK_H

#include <random>

class RandomWalk {
public:

    explicit RandomWalk(size_t interactions);

    bool init();

    bool start();

    bool stop();

    bool destroy();

private:

    const int WIDTH{640};
    const int HEIGHT{480};

    size_t interactions;

    SDL_Window *window;
    SDL_Surface *screen_surface;
    SDL_Renderer *renderer;
    SDL_Surface *walk_surface;
    SDL_Texture *grid_texture;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist_width;
    std::uniform_int_distribution<int> dist_height;
    bool _load_grid();
    int _get_random_width();
    int _get_random_height();
};


#endif //SDL2HELLO_RANDOMWALK_H
