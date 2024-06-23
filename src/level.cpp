#include "level.hpp"

void pushPlain(vector<UIprimitive> *p_vector, int c_r, int c_g, int c_b, int c_a, int r_x, int r_y, int r_w, int r_h)
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
    primitive.color = color;
    primitive.rect = rect;
    p_vector->push_back(primitive);
}

void pushButton(vector<UIprimitive> *p_vector, int c_r, int c_g, int c_b, int c_a, int r_x, int r_y, int r_w, int r_h, string text)
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
    primitive.color = color;
    primitive.rect = rect;
    primitive.textButton = text;
    p_vector->push_back(primitive);
}

Level::Level(int p_windowX, int p_windowY)
    :_windowX(p_windowX), _windowY(p_windowY), _world(((p_windowX - p_windowX/8)/5)+1, (p_windowY/5)+1)
{
    loadLevel(0);
};

void Level::loadLevel(int levelID)
{
    _world.erease();
    _buttons.clear();
    _plains.clear();
    pushPlain(&_plains, 0, 0, 0, 255, 0, 0, _windowX, _windowY); // background

    switch (levelID)
    {
        case 0: // main menu
        {
            _world.randomFill();
            pushPlain(&_plains, 10, 10, 10, 255, _windowX - (_windowX/8), 0, _windowX/8, _windowY); // right side bar
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/32, (_windowX/16) + _windowX/32, _windowY/16 + _windowY/64, "Start"); // start button
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/8, (_windowX/16) + _windowX/32, _windowY/16 + _windowY/64, "Settings"); // settings button
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY - _windowY/8 + _windowY/64, (_windowX/16) + _windowX/32, _windowY/16 + _windowY/64, "Exit"); // exit button
            break;
        }
        case 1: // game itself
        {
            pushPlain(&_plains, 10, 10, 10, 255, _windowX - (_windowX/8), 0, _windowX/8, _windowY); // right side bar
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY - _windowY/5, (_windowX/16) + _windowX/32, _windowY/16 + _windowY/64, "Menu"); // menu button
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY - _windowY/8 + _windowY/64, (_windowX/16) + _windowX/32, _windowY/16 + _windowY/64, "Pause"); // exit button
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/32, _windowX/24, _windowY/24, "WATER"); // water selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - (_windowX/17.7), _windowY/32, _windowX/24, _windowY/24, "SAND"); // sand selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/12, _windowX/24, _windowY/24, "FIRE"); // fire selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - (_windowX/17.7), _windowY/12, _windowX/24, _windowY/24, "WOOD"); // wood selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/7.3, _windowX/24, _windowY/24, "SMOKE"); // fire selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - (_windowX/17.7), _windowY/7.3, _windowX/24, _windowY/24, "STEAM"); // wood selection
            pushButton(&_buttons, 40, 40, 40, 255, _windowX - ((_windowX/8) - _windowX/64), _windowY/5.3, _windowX/24, _windowY/24, "STEEL"); // fire selection
            //pushButton(&_buttons, 40, 40, 40, 255, _windowX - (_windowX/17.7), _windowY/5.3, _windowX/24, _windowY/24, "STEAM"); // wood selection
            break;
        }
    }

    _level = levelID;
}

void Level::updateWorld()
{
    switch (_level)
    {
        case 0:
        {
            _world.updateMenu();
            break;
        }
        case 1:
        {
            _world.updateGame();
            break;
        }
    }
}

int Level::getPlainCount()
{
    return _plains.size();
}

int Level::getButtonCount()
{
    return _buttons.size();
}

UIprimitive* Level::getPlain(int p_i)
{
    return &_plains[p_i];
}

UIprimitive* Level::getButton(int p_i)
{
    return &_buttons[p_i];
}
World* Level::getWorld()
{
    return &_world;
}