#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
    :_window(NULL), _renderer(NULL)
{
    _window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
    if (_window == NULL)
    {
        std::cout << "Couldn't create window!" << std::endl;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::loadTextures(const char* p_img_directory)
{
    SDL_Texture* texture = NULL;
    string texture_path;
    for(int i = 0; i < size(textures); i++)
    {
        texture_path = p_img_directory + to_string(i + 1) + ".jpg";
        textures[i] = IMG_LoadTexture(_renderer,  texture_path.c_str());
        if (texture == NULL)
        {
            std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
        }
    }
}

void RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void RenderWindow::renderEntity(entity& p_entity)
{
	SDL_Rect src; 
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopy(_renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::renderWorld(world& p_world)
{
    SDL_Rect dst;
    dst.w = 10 * renderScale;
    dst.h = 10 * renderScale;

    for (int i = 0; i < p_world.getHeight(); i++)
    {
        for (int j = 0; j < p_world.getWidth(); j++)
        {
            dst.x = 10 * (i);
            dst.y = 10 * (j);
            SDL_RenderCopy(_renderer, textures[p_world.getCell(i,j).getEntityID()], NULL, &dst);
        }
    }
    SDL_RenderPresent(_renderer);
}

void RenderWindow::celanUp()
{
    SDL_DestroyWindow(_window);
}

