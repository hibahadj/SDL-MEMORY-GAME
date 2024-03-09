#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Rect textWon = {100, 100, 200, 150};

void won(SDL_Renderer* renderer, SDL_Rect destination, char* url)
{
    SDL_Surface *menu = SDL_LoadBMP(url);
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_FreeSurface(menu);
    SDL_RenderCopy(renderer, txt, NULL, &destination);
    SDL_DestroyTexture(txt);
}

void closeSDLWon(SDL_Window *window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void loadttfWon(SDL_Renderer *renderer, const char *text, int x, int y, int wth, int hght)
{
    TTF_Font* font = TTF_OpenFont("font/Miglia.ttf", 45);
    if (!font)
    {
        printf("font not find! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_QueryTexture(texture, NULL, NULL, &textWon.w, &textWon.h);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_Rect recttitre = {x, y, textWon.w, hght};
    SDL_RenderCopy(renderer, texture, NULL, &recttitre);
    SDL_DestroyTexture(texture);
}


void afficherWon(SDL_Window* window,SDL_Renderer* renderer, int score,int isCpuWon)
{
    int running = 1;
    char url[200];
    char str[17];

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        closeSDLBest(window, renderer);
        return 1;
    }

    if(isCpuWon == 0)
    {
        strcpy(url,"image/youwon.bmp");
    }
    else
    {
        strcpy(url,"image/cpuwon.bmp");
    }
    SDL_Rect destination = {0, 0, 800, 600};
    won(renderer, destination, url);

    strcpy(url,"image/back.bmp");
    SDL_Rect destination1 = {13, 13, 67, 67};
    won(renderer, destination1, url);
    SDL_RenderPresent(renderer);

    sprintf(str, "%d", score);
    loadttfWon(renderer, str, 410, 262, 180, 40);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(running==1)
    {

        while (SDL_PollEvent(&event)!= 0)
        {
            int x1, y1;

            x1 = event.motion.x;
            y1 = event.motion.y;

            if(event.type == SDL_QUIT)
            {
                running = 0;
                closeSDLBest(window, renderer);
            }
            if (event.type == SDL_MOUSEBUTTONUP && x1 <= 80 && x1 >= 13 && y1 <= 80 && y1 >= 13)
            {
                printf("Back to menu!\n");
                SDL_DestroyRenderer(renderer);
                running = 0;
            }
                        if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    printf("Back to menu!\n");
                    SDL_DestroyRenderer(renderer);
                    running = 0;
                }
            }
        }
    }
}

