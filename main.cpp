#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "src/renderWindow.hpp"
#include "src/entity.hpp"
#include "src/cell.hpp"
#include "src/world.hpp"

using namespace std;

int main(int argc, char ** args)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cout << "SDL_ERROR: " << SDL_GetError() << std::endl; }
    if (!(IMG_Init(IMG_INIT_PNG))) { std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;}
    
    RenderWindow window("game V0.0.1", 1280, 720);
    
    window.loadTextures("res\\img\\");

    world world(128, 72);
    bool gameRunning = true;
    SDL_Event event;

    int mouse_x, mouse_y;

    while(gameRunning) 
    {
        Uint64 start = SDL_GetPerformanceCounter();
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }
        window.clear();
        SDL_GetMouseState(&mouse_x, &mouse_y);

        window.renderWorld(world);
        
        //FPS
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        cout << "Current FPS: " << to_string(1.0f / elapsed) << endl;
    }

    window.celanUp();
    SDL_Quit();
    return 0;
}