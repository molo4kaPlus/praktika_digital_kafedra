#pragma once

#include <vector>

#include "cell.hpp"

using namespace std;

class World
{
    private:
        int height;
        int width;
        vector<vector<cell>> World_grid;
    public:
        World(unsigned int p_width, int p_height);
        int getHeight();
        int getWidth();
        cell getCell(int p_x, int p_y);
        void setCell(int p_x, int p_y, cell p_cell);
};