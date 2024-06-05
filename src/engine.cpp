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
    world = new World(windowWidth/10, windowHeight/10);
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
    int i = 1;
}

void game::render()
{
    SDL_RenderClear(renderer);

    SDL_Rect dst;
    dst.w = 10;
    dst.h = 10;

    for (int i = 0; i < world->getHeight(); i++)
    {
        for (int j = 0; j < world->getWidth(); j++)
        {
            dst.x = 10 * j;
            dst.y = 10 * i;
            SDL_RenderCopy(renderer, textures[world->getCell(j,i).getEntityID()], NULL, &dst);
        }
    }
    SDL_RenderPresent(renderer);
}

void game::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}