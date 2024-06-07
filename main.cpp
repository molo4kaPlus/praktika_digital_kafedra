#include "src/engine.hpp"

using namespace std;

int main(int argc, char ** args)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { cout << "SDL_ERROR: " << SDL_GetError() << endl; }
    if (!(IMG_Init(IMG_INIT_PNG))) { cout << "IMG_init has failed. Error: " << SDL_GetError() << endl; }
    if (!(TTF_Init())) { cout << "TTF_init has failed. Error: " << SDL_GetError() << endl; }
    
    game game("game V0.0.3", 1280, 720);

    bool gameRunning = true;

    game.init();
    while(gameRunning) 
    {
        game.handleEvents(gameRunning);
        game.update();
        game.render();
        SDL_Delay(100);
    }
    game.cleanUp();
    return 0;
}