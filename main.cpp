#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "src/engine.hpp"

using namespace std;

int main(int argc, char ** args)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cout << "SDL_ERROR: " << SDL_GetError() << std::endl; }
    if (!(IMG_Init(IMG_INIT_PNG))) { std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;}
    
    game game("game V0.0.2", 1280, 720);

    bool gameRunning = true;
    SDL_Event event;

    int mouse_x, mouse_y;

    game.init();
    while(gameRunning) 
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }
        game.update();
        game.render();
    }
    game.cleanUp();
    return 0;
}