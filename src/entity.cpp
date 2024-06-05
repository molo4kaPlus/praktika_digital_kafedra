#include "entity.hpp"

entity::entity(float p_x, float p_y, SDL_Texture* p_texture)
    :x(p_x), y(p_y), texture(p_texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 10;
	currentFrame.h = 10;
}

float entity::getX()
{
    return x;
}

void entity::setX(float p_x)
{
    x = p_x;
}

void entity::setY(float p_y)
{
    y = p_y;
}


float entity::getY()
{
    return y;
}

SDL_Texture* entity::getTexture()
{
    return texture;
}

SDL_Rect entity::getCurrentFrame()
{
    return currentFrame;
}