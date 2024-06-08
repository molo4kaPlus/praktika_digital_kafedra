#pragma once

#include <SDL.h>
#include <queue>

#include "world.hpp"
/*
0 - plane
1 - button
*/
struct UIprimitive
{
    SDL_Rect rect;
    SDL_Color color;
    string textButton;
    string fontPath = "res/fonts/GOST Common.ttf";
    bool mouseOnMe = false;
    bool pressed = false;
};

class Level
{
    private:
        World _world;
        vector<UIprimitive> _plains;
        vector<UIprimitive> _buttons;
        int _level;
        int _windowX;
        int _windowY;
    public:
        Level(int p_level, int p_windowX, int p_windowY);
        int getButtonCount();
        int getPlainCount();
        UIprimitive& getPlain(int p_i);
        UIprimitive& getButton(int p_i);
        void setColorFromVec(int p_i, int p_r, int p_g, int p_b, int p_a);
        void loadLevel(int levelID);
};
