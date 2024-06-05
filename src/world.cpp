#include "world.hpp"

World::World(unsigned int p_width, int p_height)
{
    height = p_height;
    width = p_width;
    World_grid = {p_width, vector<cell>(p_height, cell(0))};
}

cell World::getCell(int p_x, int p_y)
{
    return World_grid[p_x][p_y];
}

void World::setCell(int p_x, int p_y, cell p_cell)
{
    World_grid[p_x][p_y] = p_cell;
}

int World::getHeight()
{
    return height;
}

int World::getWidth()
{
    return width;
}

void World::randomFill()
{
    for (int x = 1; x < width - 1; x++)
    {
        for (int y = 1; y < height - 1; y++)
        {
            World_grid[x][y] = (rand() % 2) - 1;
        }
    }
}