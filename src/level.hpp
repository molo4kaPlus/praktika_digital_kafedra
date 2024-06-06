#pragma once

#include <SDL.h>

#include "world.hpp"
/*
0 - plane
*/
struct UIprimitive
{
    SDL_Rect rect;
    SDL_Color color;
    int type;
};

class Level
{
    private:
        World _world;
        std::vector<UIprimitive> _rects;
        int _level;
        int _windowX;
        int _windowY;
    public:
        Level(int p_level, int p_windowX, int p_windowY);
        SDL_Rect& getRectFromVec(int p_i);
        SDL_Color& getColorFromVec(int p_i);
        int getRectCount();
        void loadLevel(int levelID);
};
