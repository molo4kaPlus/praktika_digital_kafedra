#pragma once

#include <SDL.h>

#include "world.hpp"
/*
0 - plane
1 - button
*/
struct UIprimitive
{
    SDL_Rect rect;
    SDL_Color color;
    int type;
    string textButton;
    string fontPath = "res/fonts/GOST Common.ttf";
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
        void setColorFromVec(int p_i, int p_r, int p_g, int p_b, int p_a);
        int getTypeFromVec(int p_i);
        string getFontFileFromVec(int p_i);
        string getTextFromVec(int p_i);
        int getRectCount();
        void loadLevel(int levelID);
};
