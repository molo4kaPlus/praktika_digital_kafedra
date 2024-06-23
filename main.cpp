#include "src/engine.hpp"

using namespace std;

int main(int argc, char ** args)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { cout << "SDL_ERROR: " << SDL_GetError() << endl; }
    if (!(IMG_Init(IMG_INIT_PNG))) { cout << "IMG_init has failed. Error: " << SDL_GetError() << endl; }
    if ((TTF_Init() != 0)) { cout << "TTF_init has failed. Error: " << SDL_GetError() << endl; }
    
    game game("game V0.1.1", 1280, 720);

    bool gameRunning = true;

    game.init();
    while(gameRunning) 
    {
        Uint64 start = SDL_GetPerformanceCounter();
        game.update();
        game.handleEvents(gameRunning);
        game.render();
        Uint64 end = SDL_GetPerformanceCounter();
        //SDL_Delay(100);
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        //cout << "Current FPS: " << to_string(1.0f / elapsed) << endl;
    }
    game.cleanUp();
    return 0;
}