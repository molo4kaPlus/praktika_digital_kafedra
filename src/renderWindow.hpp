#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "entity.hpp"
#include "world.hpp"

class RenderWindow
{
    public:
        RenderWindow(const char* p_title, int p_width, int p_height);
        void loadTextures(const char* p_img_directory);
        void clear();
        void render(entity& p_entity);
        void renderWorld(world& p_world);
        void renderEntity(entity& p_entity);
        void celanUp();
    private:
        float renderScale = 1.0f;
        SDL_Texture* textures[2];
        SDL_Window* _window;
        SDL_Renderer* _renderer;
};