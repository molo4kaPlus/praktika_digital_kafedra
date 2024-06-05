#include "engine.hpp"

game::game(const char* p_title, int p_width, int p_height)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Couldn't create window!" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void game::init()
{
    /// loading textures
    string texture_path;
    int texturesCount = 0;
    for(int i = 0; i < size(textures); i++)
    {
        texture_path = "res\\img\\" + to_string(i + 1) + ".jpg";
        textures[i] = IMG_LoadTexture(renderer,  texture_path.c_str());
        if (textures[i] == NULL)
        {
            std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
        }
        else { texturesCount++; }
    }
    cout << "Loaded " << texturesCount << " textures." << endl;
    
    /// creating world
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    world0 = new World(windowWidth/10, windowHeight/10);
    srand(time(NULL));
    world0->randomFill();
}

void game::handleEvents(bool &gameRunning)
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameRunning = false;
        }
    }
}

void game::update()
{
    world1 = new World(windowWidth/10, windowHeight/10);
    bool C, R, L, D, U, RU, LU, RD, LD;
    int count;
    for (int x = 1; x < world0->getWidth() - 1; x++)
    {
        for (int y = 1; y < world0->getHeight() - 1; y++)
        {
            U = world0->getCell(x, y + 1).getEntityID();
            D = world0->getCell(x, y - 1).getEntityID();
            R = world0->getCell(x + 1, y).getEntityID();
            RU = world0->getCell(x + 1, y + 1).getEntityID();
            RD = world0->getCell(x + 1, y - 1).getEntityID();
            L = world0->getCell(x - 1, y).getEntityID();
            LU = world0->getCell(x - 1, y + 1).getEntityID();
            LD = world0->getCell(x - 1, y - 1).getEntityID();
            count = R + RU + RD + L + LU + LD + D + U;
            if ((count == 3) && (world0->getCell(x, y).getEntityID() == 0)) { world1->setCell(x, y, cell(1)); }
            else if ((count == 3) && (world0->getCell(x, y).getEntityID() == 1)) { world1->setCell(x, y, cell(1)); }
            else if ((count == 2) && (world0->getCell(x, y).getEntityID() == 1)) { world1->setCell(x, y, cell(1)); }
            else { world1->setCell(x, y, cell(0)); }
        }
    }
    world0 = world1;
}

void game::render()
{
    SDL_RenderClear(renderer);

    SDL_Rect dst;
    dst.w = 10;
    dst.h = 10;

    for (int i = 0; i < world0->getHeight(); i++)
    {
        for (int j = 0; j < world0->getWidth(); j++)
        {
            dst.x = 10 * j;
            dst.y = 10 * i;
            SDL_RenderCopy(renderer, textures[world0->getCell(j,i).getEntityID()], NULL, &dst);
        }
    }
    SDL_RenderPresent(renderer);
}

void game::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}