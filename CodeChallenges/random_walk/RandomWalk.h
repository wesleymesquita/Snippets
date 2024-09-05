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

    static constexpr int WIDTH{640};
    static const int HEIGHT{480};
    static const int SQUARE_SIZE{20};

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
    std::uniform_int_distribution<int> dist_square_height;
    std::uniform_int_distribution<int> dist_square_width;

    bool _draw_grid(int square_size);
    void _paint_square(int x, int y, int square_size);
    void _get_random_square(SDL_Rect *square);
    int _get_random_width();
    int _get_random_height();
};


#endif //SDL2HELLO_RANDOMWALK_H
