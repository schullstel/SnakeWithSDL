#undef main
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Drawer.hpp"

int main()
{
    Drawer drawer;
    drawer.initDrawer();
    drawer.loadMedia();
    drawer.exec();
    drawer.close();

    return 0;
}
