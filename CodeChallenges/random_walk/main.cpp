#include "SDL.h"
#include "RandomWalk.h"

int main(int argc, char *argv[])
{
    RandomWalk rw(10);
    rw.init();
    rw.start();
    rw.destroy();
    return 0;
}