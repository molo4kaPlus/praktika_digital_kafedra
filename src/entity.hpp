#pragma once

#include <SDL.h>
#include <SDL_image.h>

class entity
{
    public:
        entity(float p_x, float p_y, SDL_Texture* p_texture);
        float getX();
        float getY();
        void setY(float p_y);
        void setX(float p_x);
        SDL_Texture* getTexture();
        SDL_Rect getCurrentFrame();
    private:
        float x, y;
        SDL_Rect currentFrame;
        SDL_Texture* texture;
};