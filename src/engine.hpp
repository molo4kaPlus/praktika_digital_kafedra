#pragma once

using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "world.hpp"
#include "level.hpp"

class game
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* textures[10];
        SDL_Event event;
        Level level;
        int windowWidth, windowHeight;
        int _currentPaintID;
    public:
        game(const char* p_title, int p_width, int p_height);
        void init();
        void handleEvents(bool &gameRunning);
        void update();
        void render();
        void cleanUp();
};

