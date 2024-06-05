#pragma once

using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#include "renderWindow.hpp"
#include "world.hpp"

class game
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* textures[10];
        SDL_Event event;
        World* world;
        int windowWidth, windowHeight;

    public:
        game(const char* p_title, int p_width, int p_height);
        void init();
        void handleEvents(bool &gameRunning);
        void update();
        void render();
        void cleanUp();
};

