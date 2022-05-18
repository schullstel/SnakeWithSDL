#undef main
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Drawer.hpp"

int main()
{
    std::cout << "Piesek 12134" << std::endl;
    Drawer drawer;
    std::cout << "Piesek 12134" << std::endl;
    drawer.initDrawer();
    drawer.loadMedia();
    drawer.exec();
    drawer.close();

    std::cout << "Piesek" << std::endl;

    return 0;
}
