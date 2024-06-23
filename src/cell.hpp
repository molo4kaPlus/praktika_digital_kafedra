#pragma once
#include <SDL.h>
// 0 - space
// 1 - white dot
// 2 - sand
// 3 - water
// 4 - wood
// 5 - fire
// 6 - smoke
// 7 - steam
// 8 - steel

class cell
{
    private:
        int entityID;
        int lifeTime;
        int density;
        bool flamable = false;
        SDL_Color color;
    public:
        bool hasBeenUpdated = false;
        bool isMetal = false;
        int temp;
        cell(int p_entityID);
        int getDens();
        void reduceLifeTime(int p_lifeTime);
        void setID(int p_entityID);
        void setColor(SDL_Color p_color);
        int getEntityID();
        int getlifeTime();
        bool hasGravity();
        bool isFlamable();
        SDL_Color getColor();
};  