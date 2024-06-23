#include "cell.hpp"

cell::cell(int p_entityID)
{
    switch (p_entityID)
    {
        case 0: // 0 - space
        {
            entityID = 0;
            density = 0;
            color = {1, 1, 1, 255};
            break;
        }
        case 1: // 1 - white dot
        { 
            entityID = 1;
            density = 999;
            color = {255, 255, 255, 255};
            break;
        }
        case 2: // 2 - sand
        {
            entityID = 2;
            density = 30;
            color = {255, 255, 0, 255};
            break;
        }
        case 3: // 3 - water
        {
            entityID = 3;
            density = 10;
            color = {52, 79, 254, 255};
            break;
        }
        case 4: // 4 - wood
        {
            entityID = 4;
            density = 15;
            color = {146, 109, 5, 255};
            flamable = true;
            break;
        }
        case 5: // 5 - fire
        {
            entityID = 5;
            lifeTime = 340;
            density = 0;
            color = {205, 72, 41, 255};
            break;
        }
        case 6: // 6 - smoke
        {
            entityID = 6;
            density = 4;
            color = {92, 92, 92, 255};
            break;
        }
        case 7: // 7 - steam
        {
            entityID = 7;
            density = 5;
            lifeTime = 240;
            color = {74, 81, 101, 255};
            break;
        }
        case 8: // 8 - steel
        {
            entityID = 8;
            density = 40;
            isMetal = true;
            temp = 0;
            lifeTime = 240;
            color = {128, 142, 181, 255};
            break;
        }
    }
}

int cell::getEntityID()
{
    return entityID;
}

int cell::getlifeTime()
{
    return lifeTime;
}

int cell::getDens()
{
    return density;
}

void cell::setID(int p_entityID)
{
    entityID = p_entityID;
}

void cell::reduceLifeTime(int p_lifeTime)
{
    lifeTime -= p_lifeTime;
}

bool cell::isFlamable()
{
    return flamable;
}

void cell::setColor(SDL_Color p_color)
{
    color = p_color;
}

SDL_Color cell::getColor()
{
    return color;
}
