#include "world.hpp"

World::World(unsigned int p_width, int p_height)
{
    height = p_height + 1;
    width = p_width + 1;
    World_grid = {p_width, vector<cell>(height, cell(0))};
    World_1 = {p_width, vector<cell>(width, cell(0))};
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
    for (int x = 0; x < width - 1; x++)
    {
        for (int y = 0; y < height - 1; y++)
        {
            World_grid[x][y] = cell((rand() % 2));
        }
    }
}

void World::updateMenu()
{
    bool C, R, L, D, U, RU, LU, RD, LD, flag;
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
            if ((count == 3) && (World_grid[x][y].getEntityID() == 0)) { World_1[x][y] = cell(1); }
            else if ((count == 3) && (World_grid[x][y].getEntityID() == 1)) { World_1[x][y] = cell(1); }
            else if ((count == 2) && (World_grid[x][y].getEntityID() == 1)) { World_1[x][y] = cell(1); }
            else { World_1[x][y] = cell(0); }
        }
    }
    for (int x = 0; x < World_grid.size(); x++)
    {
        for (int y = 0; y <  World_grid[0].size(); y++)
        {
            World_grid[x][y] = World_1[x][y];
        }
    }    
}

void World::updateGame()
{
    for (int x = 1; x < World_grid.size() - 1; x++)
    {
        for (int y = 0; y < World_grid[0].size() - 3; y++)
        {
            switch (World_grid[x][y].getEntityID())
            {
                //space
                case 0:
                {
                    World_grid[x][y].hasBeenUpdated = true;
                    break;
                }
                
                //white dot
                case 1:
                {
                    World_grid[x][y].hasBeenUpdated = true;
                    break;
                }
                
                //sand
                case 2:
                {
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;

                    //fall
                    if(World_grid[x][y+1].getEntityID() == 0){
                        World_grid[x][y+1] = cell(2);
                        World_grid[x][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if(World_grid[x + 1][y+1].getEntityID() == 0){
                        World_grid[x+1][y+1] = cell(2);
                        World_grid[x+1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if(World_grid[x - 1][y+1].getEntityID() == 0){
                        World_grid[x-1][y+1] = cell(2);
                        World_grid[x-1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    //swap
                    else if(World_grid[x][y].getDens() > World_grid[x][y+1].getDens()){
                        cell tempCell = World_grid[x][y+1];
                        World_grid[x][y+1] = World_grid[x][y];
                        World_grid[x][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x+1][y+1].getDens()){
                        cell tempCell = World_grid[x+1][y+1];
                        World_grid[x+1][y+1] = World_grid[x][y];
                        World_grid[x+1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x-1][y+1].getDens()){
                        cell tempCell = World_grid[x-1][y+1];
                        World_grid[x-1][y+1] = World_grid[x][y];
                        World_grid[x-1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }

                    break;
                }
                
                //water
                case 3:
                {
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;
                    if ((World_grid[x][y + 1].getEntityID() == 0)){
                        World_grid[x][y + 1] = cell(3);
                        World_grid[x][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x + 1][y + 1].getEntityID() == 0)){
                        World_grid[x + 1][y + 1] = cell(3);
                        World_grid[x+1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x - 1][y + 1].getEntityID() == 0)){
                        World_grid[x - 1][y + 1] = cell(3);
                        World_grid[x-1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if (rand() % 2 == 0)
                    {
                        if (World_grid[x + 1][y].getEntityID() == 0){
                            World_grid[x + 1][y] = cell(3);
                            World_grid[x+1][y].hasBeenUpdated = true;
                            World_grid[x][y] = cell(0);
                        }
                    }
                    else if (World_grid[x - 1][y].getEntityID() == 0){
                        World_grid[x - 1][y] = cell(3);
                        World_grid[x-1][y].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }

                    //swap
                    else if(World_grid[x][y].getDens() > World_grid[x][y+1].getDens()){
                        cell tempCell = World_grid[x][y+1];
                        World_grid[x][y+1] = World_grid[x][y];
                        World_grid[x][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x+1][y+1].getDens()){
                        cell tempCell = World_grid[x+1][y+1];
                        World_grid[x+1][y+1] = World_grid[x][y];
                        World_grid[x+1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x-1][y+1].getDens()){
                        cell tempCell = World_grid[x-1][y+1];
                        World_grid[x-1][y+1] = World_grid[x][y];
                        World_grid[x-1][y+1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    break;
                }

                //wood
                case 4:
                {
                    World_grid[x][y].hasBeenUpdated = true;
                    break;
                }

                //fire
                case 5:
                {
                    World_grid[x][y].reduceLifeTime(1);
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;
                    
                    if(World_grid[x][y].getlifeTime() <= 0){
                        if(rand() % 5 == 0){
                            World_grid[x][y] = cell(6);
                        }
                        break;
                    }

                    

                    // fire time
                    if(World_grid[x][y].getlifeTime() % 20 == 0){
                        if(World_grid[x][y-1].getEntityID() == 0 && (rand() % 3 == 0)){
                            World_grid[x][y-1] = cell(5);
                            World_grid[x][y-1].reduceLifeTime(300);
                            World_grid[x][y-1].hasBeenUpdated = true;
                        }
                    }
                    if(World_grid[x][y].getlifeTime() % 20 == 0){
                        if(World_grid[x+1][y-1].getEntityID() == 0 && (rand() % 3 == 0)){
                            World_grid[x+1][y-1] = cell(5);
                            World_grid[x+1][y-1].reduceLifeTime(300);
                            World_grid[x+1][y-1].hasBeenUpdated = true;
                        }
                    }
                    if(World_grid[x][y].getlifeTime() % 20 == 0){
                        if(World_grid[x-1][y-1].getEntityID() == 0 && (rand() % 3 == 0)){
                            World_grid[x-1][y-1] = cell(5);
                            World_grid[x-1][y-1].reduceLifeTime(300);
                            World_grid[x-1][y-1].hasBeenUpdated = true;
                        }
                    }

                    /*
                    if(World_grid[x][y].getlifeTime() % 300 == 0){
                        if(World_grid[x][y-1].getEntityID() == 0){
                            World_grid[x][y-1] = cell(6);
                            World_grid[x][y-1].hasBeenUpdated = true;
                        }
                        else if(World_grid[x+1][y].getEntityID() == 0){
                            World_grid[x+1][y] = cell(6);
                            World_grid[x+1][y].hasBeenUpdated = true;
                        }
                        else if(World_grid[x-1][y].getEntityID() == 0){
                            World_grid[x-1][y] = cell(6);
                            World_grid[x-1][y].hasBeenUpdated = true;
                        }
                    }
                    */
                    if(World_grid[x][y+1].getEntityID() == 3){
                        World_grid[x][y] = cell(7);
                    }
                    else if(World_grid[x][y-1].getEntityID() == 3){
                        World_grid[x][y] = cell(7);
                    }
                    else if(World_grid[x+1][y].getEntityID() == 3){
                        World_grid[x][y] = cell(7);
                    }
                    else if(World_grid[x-1][y].getEntityID() == 3){
                        World_grid[x][y] = cell(7);
                    }

                    // ignitor
                    if(World_grid[x][y+1].isFlamable()){
                        if(rand() % 15 == 0){
                            World_grid[x][y+1] = cell(5);
                            World_grid[x][y+1].hasBeenUpdated = true;
                        }
                    }
                    if(World_grid[x][y-1].isFlamable()){
                        if(rand() % 15 == 0){
                            World_grid[x][y+1] = cell(5);
                            World_grid[x][y+1].hasBeenUpdated = true;
                        }
                    }
                    if(World_grid[x+1][y].isFlamable()){
                        if(rand() % 15 == 0){
                            World_grid[x+1][y] = cell(5);
                            World_grid[x+1][y].hasBeenUpdated = true;
                        }
                    }
                    if(World_grid[x-1][y].isFlamable()){
                        if(rand() % 15 == 0){
                            World_grid[x-1][y] = cell(5);
                            World_grid[x-1][y].hasBeenUpdated = true;
                        }
                    }

                    // hot
                    if(World_grid[x][y-1].isMetal){
                        World_grid[x][y-1].temp += 20;
                    }
                    if(World_grid[x+1][y-1].isMetal){
                        World_grid[x+1][y-1].temp += 20;
                    }
                    if(World_grid[x-1][y-1].isMetal){
                        World_grid[x-1][y-1].temp += 20;
                    }
                    
                    break;
                }
            
                //smoke
                case 6:
                {
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;
                    if ((World_grid[x][y - 1].getEntityID() == 0 && (World_grid[x][y - 1].getEntityID() == 0))){
                        World_grid[x][y - 1] = cell(6);
                        World_grid[x][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x + 1][y - 1].getEntityID() == 0  && (World_grid[x + 1][y - 1].getEntityID() == 0))){
                        World_grid[x + 1][y - 1] = cell(6);
                        World_grid[x+1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x - 1][y - 1].getEntityID() == 0  && (World_grid[x - 1][y - 1].getEntityID() == 0))){
                        World_grid[x - 1][y - 1] = cell(6);
                        World_grid[x-1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if (rand() % 2 == 0)
                    {
                        if (World_grid[x + 1][y].getEntityID() == 0 && World_grid[x + 1][y].getEntityID() == 0){
                            World_grid[x + 1][y] = cell(6);
                            World_grid[x+1][y].hasBeenUpdated = true;
                            World_grid[x][y] = cell(0);
                        }
                    }
                    else if (World_grid[x - 1][y].getEntityID() == 0 && World_grid[x - 1][y].getEntityID() == 0){
                        World_grid[x - 1][y] = cell(6);
                        World_grid[x-1][y].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }

                    //swap
                    else if(World_grid[x][y].getDens() > World_grid[x][y-1].getDens()){
                        cell tempCell = World_grid[x][y-1];
                        World_grid[x][y-1] = World_grid[x][y];
                        World_grid[x][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x+1][y-1].getDens()){
                        cell tempCell = World_grid[x+1][y+1];
                        World_grid[x+1][y-1] = World_grid[x][y];
                        World_grid[x+1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x-1][y-1].getDens()){
                        cell tempCell = World_grid[x-1][y-1];
                        World_grid[x-1][y-1] = World_grid[x][y];
                        World_grid[x-1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }

                    // hot
                    if(World_grid[x][y-1].isMetal){
                        World_grid[x][y-1].temp += 2;
                    }
                    if(World_grid[x+1][y-1].isMetal){
                        World_grid[x+1][y-1].temp += 2;
                    }
                    if(World_grid[x-1][y-1].isMetal){
                        World_grid[x-1][y-1].temp += 2;
                    }
                    break;
                }
            
                //steam
                case 7:
                {
                    World_grid[x][y].reduceLifeTime(1);
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;
                    if (World_grid[x][y].getlifeTime() <= 0){
                        World_grid[x][y] = cell(3);
                    }

                    if ((World_grid[x][y - 1].getEntityID() == 0)){
                        World_grid[x][y - 1] = World_grid[x][y];
                        World_grid[x][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x + 1][y - 1].getEntityID() == 0)){
                        World_grid[x + 1][y - 1] = World_grid[x][y];
                        World_grid[x+1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if ((World_grid[x - 1][y - 1].getEntityID() == 0)){
                        World_grid[x - 1][y - 1] = World_grid[x][y];
                        World_grid[x-1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    else if (rand() % 2 == 0)
                    {
                        if (World_grid[x + 1][y].getEntityID() == 0){
                            World_grid[x + 1][y] = World_grid[x][y];
                            World_grid[x+1][y].hasBeenUpdated = true;
                            World_grid[x][y] = cell(0);
                        }
                    }
                    else if (World_grid[x - 1][y].getEntityID() == 0){
                        World_grid[x - 1][y] = World_grid[x][y];
                        World_grid[x-1][y].hasBeenUpdated = true;
                        World_grid[x][y] = cell(0);
                    }
                    //swap
                    else if(World_grid[x][y].getDens() > World_grid[x][y-1].getDens()){
                        cell tempCell = World_grid[x][y-1];
                        World_grid[x][y-1] = World_grid[x][y];
                        World_grid[x][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x+1][y-1].getDens()){
                        cell tempCell = World_grid[x+1][y+1];
                        World_grid[x+1][y-1] = World_grid[x][y];
                        World_grid[x+1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    else if(World_grid[x][y].getDens() > World_grid[x-1][y-1].getDens()){
                        cell tempCell = World_grid[x-1][y-1];
                        World_grid[x-1][y-1] = World_grid[x][y];
                        World_grid[x-1][y-1].hasBeenUpdated = true;
                        World_grid[x][y] = tempCell;
                    }
                    break;
                }
            
                //steel
                case 8:
                {
                    if(World_grid[x][y].temp > 0 && (rand() % 4 ==0)){
                        if(World_grid[x][y+1].getEntityID() != 8){
                            World_grid[x][y].temp -= 1; 
                        }
                        else if(World_grid[x][y-1].getEntityID() != 8){
                            World_grid[x][y].temp -= 1; 
                        }
                        else if(World_grid[x+1][y].getEntityID() != 8){
                            World_grid[x][y].temp -= 1; 
                        }
                        else if(World_grid[x-1][y].getEntityID() != 8){
                            World_grid[x][y].temp -= 1; 
                        }
                    }
                    if (World_grid[x][y].hasBeenUpdated) { break; }
                    World_grid[x][y].hasBeenUpdated = true;

                    // vaporize water
                    if(World_grid[x][y].temp > 100){
                        World_grid[x][y].setColor({158, 121, 103, 255});
                        if(World_grid[x][y-1].getEntityID() == 3){
                            World_grid[x][y-1] = cell(7);
                            World_grid[x][y-1].hasBeenUpdated = true;
                        }
                        else if(World_grid[x+1][y-1].getEntityID() == 3){
                            World_grid[x+1][y-1] = cell(7);
                            World_grid[x+1][y-1].hasBeenUpdated = true;
                        }
                        else if(World_grid[x-1][y-1].getEntityID() == 3){
                            World_grid[x-1][y-1] = cell(7);
                            World_grid[x-1][y-1].hasBeenUpdated = true;
                        }
                    }
                    else {World_grid[x][y].setColor({128, 142, 181, 255});}

                    // set the limits
                    if(World_grid[x][y].temp > 300) { World_grid[x][y].temp = 300; }

                    // share temp
                    if((World_grid[x][y-1].getEntityID() == 8) && (World_grid[x][y].temp > World_grid[x][y-1].temp)){
                        if(rand() % 4 == 0){
                            World_grid[x][y].temp -= 10;
                            World_grid[x][y-1].temp += 10;
                        }
                    }
                    if((World_grid[x][y+1].getEntityID() == 8) && (World_grid[x][y].temp > World_grid[x][y+1].temp)){
                        if(rand() % 4 == 0){
                            World_grid[x][y].temp -= 10;
                            World_grid[x][y+1].temp += 10;
                        }
                    }
                    if((World_grid[x+1][y].getEntityID() == 8) && (World_grid[x][y].temp > World_grid[x+1][y].temp)){
                        if(rand() % 4 == 0){
                            World_grid[x][y].temp -= 10;
                            World_grid[x+1][y].temp += 10;
                        }
                    }
                    if((World_grid[x-1][y].getEntityID() == 8) && (World_grid[x][y].temp > World_grid[x-1][y].temp)){
                        if(rand() % 4 == 0){
                            World_grid[x][y].temp -= 10;
                            World_grid[x-1][y].temp += 10;
                        }
                    }

                    break;
                }
            }
        }
    }
    for (int x = 1; x < World_grid.size() - 1; x++)
    {
        for (int y = 1; y < World_grid[0].size() - 1; y++)
        {
            World_grid[x][y].hasBeenUpdated = false;
        }
    }
    //World_grid = World_1;
}

void World::erease()
{
    for (int x = 0; x < World_grid.size(); x++)
    {
        for (int y = 0; y < World_grid[0].size(); y++)
        {
            World_grid[x][y] = cell(0);
        }
    }
    for (int x = 0; x < World_1.size(); x++)
    {
        for (int y = 0; y < World_1[0].size(); y++)
        {
            World_1[x][y] = cell(0);
        }
    }
}