#include "level.hpp"

void pushPrimitive(vector<UIprimitive> *p_vector, int c_r, int c_g, int c_b, int c_a, int r_x, int r_y, int r_w, int r_h, int p_type)
{
    SDL_Color color;
    SDL_Rect rect;
    UIprimitive primitive;
    color.a = c_a;
    color.r = c_r;
    color.g = c_g;
    color.b = c_b;
    rect.h = r_h;
    rect.w = r_w;
    rect.x = r_x;
    rect.y = r_y;
    primitive.type = p_type;
    primitive.color = color;
    primitive.rect = rect;
    p_vector->push_back(primitive);
}

Level::Level(int p_level, int p_windowX, int p_windowY)
    :_windowX(p_windowX), _windowY(p_windowY)
{
    _level = p_level;
    _world = {};
    _rects = {};

    switch (_level)
    {
        case 0: // main menu
        {
            pushPrimitive(&_rects, 0, 0, 0, 255, 0, 0, _windowX, _windowY, 0); // background
            pushPrimitive(&_rects, 15, 15, 15, 255, _windowX - (_windowX/8), 0, _windowX/8, _windowY, 0); // right side bar
        }
    }
};

SDL_Rect& Level::getRectFromVec(int p_i)
{
    return _rects[p_i].rect;
}

SDL_Color& Level::getColorFromVec(int p_i)
{
    return _rects[p_i].color;
}

int Level::getRectCount()
{
    return _rects.size();
}