#include "engine.hpp"

game::game(const char* p_title, int p_width, int p_height)
    :window(NULL), renderer(NULL), windowHeight(p_height), windowWidth(p_width)
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
    
    /// load level
    level = new Level(0, windowWidth, windowHeight);
    /// creating world
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    world0 = new World((windowWidth - windowWidth/8)/10, windowHeight/10);
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
    world1 = new World((windowWidth - windowWidth/8)/10, windowHeight/10);
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

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);   
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}

void renderRect(SDL_Renderer *renderer, Level *level, int i)
{
    SDL_Color color = {level->getColorFromVec(i).r, level->getColorFromVec(i).g, level->getColorFromVec(i).b, level->getColorFromVec(i).a };
    SDL_Rect rect = level->getRectFromVec(i);
    switch (level->getTypeFromVec(i))
    {
        case 0: // plain
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &level->getRectFromVec(i));
            break;
        }
        case 1: // button
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &level->getRectFromVec(i));
            SDL_Texture* text = renderText(level->getTextFromVec(i), level->getFontFileFromVec(i), {255, 255, 255, 255}, 50, renderer);
            rect.x = rect.x + rect.w * 0.10;
            rect.y = rect.y + rect.h * 0.20;
            rect.h = rect.h*0.80;
            rect.w = rect.w*0.80;
            SDL_RenderCopy(renderer, text, NULL, &rect);
            break;
        }
    }
}

void game::render()
{
    SDL_RenderClear(renderer);


    SDL_Rect dst;
    dst.w = 10;
    dst.h = 10;

    for(int i = 0; i < level->getRectCount(); i++)
    {
        renderRect(renderer, level, i);
    }
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