#pragma once

#include <vector>

#include "cell.hpp"

using namespace std;

class world
{
    private:
        int height;
        int width;
        vector<vector<cell>> world_grid;
    public:
        world(unsigned int p_height, int p_width);
        int getHeight();
        int getWidth();
        cell getCell(int p_x, int p_y);
        void setCell(int p_x, int p_y, cell p_cell);
};