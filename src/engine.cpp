#include "engine.hpp"

int mouseX, mouseY;
int g_windowWidth, g_windowHeight;
bool gamePaused = false;

enum string_code {
    eStart,
    eSettings,
    eMenu,
    ePauseSim,
    eUnPauseSim,
    eWATER,
    eWOOD,
    eSAND,
    eFIRE,
    eSMOKE,
    eSTEAM,
    eSTEEL,
    eXXX,
    eExit
};

string_code hashit (std::string const& inString) {
    if (inString == "Start") return eStart;
    if (inString == "Settings") return eSettings;
    if (inString == "Exit") return eExit;
    if (inString == "Pause") return ePauseSim;
    if (inString == "Unpause") return eUnPauseSim;
    if (inString == "SAND") return eSAND;
    if (inString == "WATER") return eWATER;
    if (inString == "WOOD") return eWOOD;
    if (inString == "FIRE") return eFIRE;
    if (inString == "SMOKE") return eSMOKE;
    if (inString == "STEAM") return eSTEAM;
    if (inString == "STEEL") return eSTEEL;
    if (inString == "XXX") return eXXX;
    if (inString == "Menu") return eMenu;
}

bool insideRect(SDL_Rect* rect, int x, int y)
{
    if ((rect->x < x && rect->w + rect->x > x) && (rect->y < y && rect->h + rect->y > y))
    {
        return true;
    }
    return false;
}

SDL_Texture* renderText(const std::string &message, const std::string *fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile->c_str(), fontSize);   
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}

void renderPlane(SDL_Renderer *renderer, UIprimitive* p_plane)
{
    SDL_Color color = p_plane->color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &p_plane->rect);
}

void handleButtonColor(UIprimitive* p_button, int x, int y)
{
    if (!p_button->mouseOnMe)
    {
        if (insideRect(&p_button->rect, mouseX, mouseY))
        {
            p_button->mouseOnMe = true;
            p_button->color.r += 15;
            p_button->color.g += 15;
            p_button->color.b += 15;
            return;
        }
    }
    else
    {
        if(insideRect(&p_button->rect, mouseX, mouseY))
        {
            p_button->mouseOnMe = false;
            p_button->color.r -= 15;
            p_button->color.g -= 15;
            p_button->color.b -= 15;
            return;
        }
    }
}

void renderButton(SDL_Renderer *renderer, UIprimitive* p_button)
{
    SDL_Color color = p_button->color;
    SDL_Texture* text = renderText(p_button->textButton, &p_button->fontPath, {255, 255, 255, 255}, 50, renderer);
    SDL_Rect rect = p_button->rect;
    rect.x = rect.x + rect.w * 0.10;
    rect.y = rect.y + rect.h * 0.20;
    rect.h = rect.h*0.80;
    rect.w = rect.w*0.80;
    handleButtonColor(p_button, mouseX, mouseY);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &p_button->rect);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);
}

void handleExit(SDL_Event &event, bool &gameRunning)
{
    if (event.type == SDL_QUIT)
    {
        gameRunning = false;
    }
}

void handleButtons(SDL_Event &event, Level &level, bool &gameRunning, int &tool)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        for(int i = 0; i < level.getButtonCount(); i++){
            switch (hashit(level.getButton(i)->textButton))
            {
                case eStart:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        level.loadLevel(1);}
                    break;
                }
                case eSettings:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        cout << "settings not implemented" << endl;}
                    break;
                }
                case ePauseSim:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        level.getButton(i)->textButton = "Unpause";
                        gamePaused = true;}
                    break;
                }
                case eUnPauseSim:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        level.getButton(i)->textButton = "Pause";
                        gamePaused = false;}
                    break;
                }
                case eMenu:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        level.loadLevel(0);}
                    break;
                }
                case eXXX:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 1;}
                    break;
                }
                case eSAND:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 2;}
                    break;
                }
                case eWATER:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 3;}
                    break;
                }
                case eWOOD:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 4;}
                    break;
                }
                case eFIRE:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 5;}
                    break;
                }
                case eSMOKE:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 6;}
                    break;
                }
                case eSTEAM:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 7;}
                    break;
                }
                case eSTEEL:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        tool = 8;}
                    break;
                }
                case eExit:
                {
                    if (insideRect(&level.getButton(i)->rect, mouseX, mouseY)){
                        gameRunning = false;
                    }
                    break;
                }
            }
        }
    }
}

void checkCellInsertion(Level* level, int p_paintID, SDL_Event &event)
{
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK)
    {
        if(mouseX < (g_windowWidth - g_windowWidth/8))
        {
            int cellPixelSizeX = g_windowWidth/level->getWorld()->getWidth();
            int cellPixelSizeY = g_windowHeight/level->getWorld()->getHeight() + 1;
            int x = mouseX/cellPixelSizeX;
            int y = mouseY/cellPixelSizeY;
            level->getWorld()->setCell(x, y, cell(p_paintID));
            level->getWorld()->setCell(x+1, y, cell(p_paintID));
            level->getWorld()->setCell(x-1, y, cell(p_paintID));
            level->getWorld()->setCell(x, y+1, cell(p_paintID));
            level->getWorld()->setCell(x, y-1, cell(p_paintID));
        }
    }
}

game::game(const char* p_title, int p_width, int p_height)
    :window(NULL), renderer(NULL), windowHeight(p_height), windowWidth(p_width), level(p_width, p_height)
{
    _currentPaintID = 2;
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Couldn't create window!" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void game::init()
{
    /// loading textures
    g_windowHeight = windowHeight;
    g_windowWidth = windowWidth;
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
    
    
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    srand(time(NULL));
}

void game::handleEvents(bool &gameRunning)
{
    SDL_GetMouseState(&mouseX, &mouseY);
    checkCellInsertion(&level, _currentPaintID, event);
    while(SDL_PollEvent(&event))
    {
        handleExit(event, gameRunning);
        handleButtons(event, level, gameRunning, _currentPaintID);
    }
}

void game::update()
{
    _currentTick += 1;
    if (!gamePaused)
    {
        level.updateWorld();
    }
}

void game::render()
{
    SDL_RenderClear(renderer);


    SDL_Rect dst;
    dst.w = 5;
    dst.h = 5;
    for(int i = 0; i < level.getPlainCount(); i++){
        renderPlane(renderer, level.getPlain(i));
    }
    
    for(int i = 0; i < level.getButtonCount(); i++){
        handleButtonColor(level.getButton(i), mouseX, mouseY);
        renderButton(renderer, level.getButton(i));
    }

    SDL_Color pixelColor;
    for (int i = 0; i < level.getWorld()->getHeight() - 1; i++)
    {
        for (int j = 0; j < level.getWorld()->getWidth() - 1; j++)
        {
            dst.x = 5 * j;
            dst.y = 5 * i;
            pixelColor = level.getWorld()->getCell(j,i).getColor();
            int id = level.getWorld()->getCell(j,i).getEntityID();

            SDL_SetRenderDrawColor(renderer, pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
            SDL_RenderFillRect(renderer, &dst);
            //SDL_RenderCopy(renderer, textures[id], NULL, &dst);
        }
    }

    SDL_RenderPresent(renderer);
}

void game::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}