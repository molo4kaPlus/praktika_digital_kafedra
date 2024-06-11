#pragma once

#include <vector>
#include <random>

#include "cell.hpp"

using namespace std;

class World
{
    private:
        int height;
        int width;
        vector<vector<cell>> World_grid;
        vector<vector<cell>> World_1;
    public:
        World(unsigned int p_width, int p_height);
        World();
        int getHeight();
        int getWidth();
        cell getCell(int p_x, int p_y);
        void setCell(int p_x, int p_y, cell p_cell);
        void update();
        void randomFill();
        void erease();
};