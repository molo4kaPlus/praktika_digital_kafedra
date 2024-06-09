#include "world.hpp"

World::World(unsigned int p_width, int p_height)
{
    height = p_height;
    width = p_width;
    World_grid = {p_width, vector<cell>(p_height, cell(0))};
}

World::World()
{

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

void World::update()
{
    bool C, R, L, D, U, RU, LU, RD, LD, flag;
    World world(width, height);
    int count;
    for (int x = 1; x < World_grid.size() - 1; x++)
    {
        for (int y = 1; y < World_grid[0].size() - 1; y++)
        {
            U = World_grid[x][y+1].getEntityID();
            D = World_grid[x][y-1].getEntityID();
            R = World_grid[x+1][y].getEntityID();
            RU = World_grid[x+1][y+1].getEntityID();
            RD = World_grid[x+1][y-1].getEntityID();
            L = World_grid[x-1][y].getEntityID();
            LU = World_grid[x-1][y+1].getEntityID();
            LD = World_grid[x-1][y-1].getEntityID();
            count = R + RU + RD + L + LU + LD + D + U;
            if ((count == 3) && (World_grid[x][y].getEntityID() == 0)) { world.setCell(x, y, cell(1)); }
            else if ((count == 3) && (World_grid[x][y].getEntityID() == 1)) { world.setCell(x, y, cell(1)); }
            else if ((count == 2) && (World_grid[x][y].getEntityID() == 1)) { world.setCell(x, y, cell(1)); }
            else { world.setCell(x, y, cell(0)); }
        }
    }
    for (int x = 0; x < World_grid.size(); x++)
    {
        for (int y = 0; y < World_grid[0].size(); y++)
        {
            World_grid[x][y] = world.getCell(x, y);
        }
    }    
}