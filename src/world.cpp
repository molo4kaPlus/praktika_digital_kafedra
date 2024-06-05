#include "world.hpp"

world::world(unsigned int p_height, int p_width)
{
    height = p_height;
    width = p_width;
    world_grid = {p_height, vector<cell>(p_width, cell(0))};
}

cell world::getCell(int p_x, int p_y)
{
    return world_grid[p_x][p_y];
}

void world::setCell(int p_x, int p_y, cell p_cell)
{
    world_grid[p_x][p_y] = p_cell;
}

int world::getHeight()
{
    return height;
}

int world::getWidth()
{
    return width;
}