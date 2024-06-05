#pragma once

using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#include "renderWindow.hpp"

class game
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* textures[10];
    public:
        game();
        void update();
        void render();
        void cleanUp();
};

