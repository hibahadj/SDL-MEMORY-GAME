#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sauv.h"

int stageBest = 1, partieBest = 1;
SDL_Rect gTextBoxRectt = {100, 100, 200, 150};

void best(SDL_Renderer* renderer, SDL_Rect destination, char* url)
{
    SDL_Surface *menu = SDL_LoadBMP(url);
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_FreeSurface(menu);
    SDL_RenderCopy(renderer, txt, NULL, &destination);
    SDL_DestroyTexture(txt);
}

void closeSDLBest(SDL_Window *window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void loadttfScore(SDL_Renderer *renderer, const char *text, int x, int y, int wth, int hght)
{
    TTF_Font* font = TTF_OpenFont("font/Miglia.ttf", 30);
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

    SDL_QueryTexture(texture, NULL, NULL, &gTextBoxRectt.w, &gTextBoxRectt.h);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_Rect recttitre = {x, y, gTextBoxRectt.w, hght};
    SDL_RenderCopy(renderer, texture, NULL, &recttitre);
    SDL_DestroyTexture(texture);
}


void afficherBest(SDL_Window* window,SDL_Renderer* renderer)
{
    int running = 1,i;
    char url[200];
    char str[12];
    UserData players[5];

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

    strcpy(url,"image/bestScore.bmp");
    SDL_Rect destination = {0, 0, 800, 600};
    best(renderer, destination, url);

    strcpy(url,"image/back.bmp");
    SDL_Rect destination1 = {13, 13, 67, 67};
    best(renderer, destination1, url);
    SDL_RenderPresent(renderer);

    int n = ordreBestScore(players);
    int y = 240;
    for (i = 0; i < n; i++)
    {
        getNbDiag(players[i].level);

        loadttfScore(renderer, players[i].name, 60, y, 180, 30);

        sprintf(str, "%d", players[i].score);
        loadttfScore(renderer, str, 265, y, 80, 30);

        sprintf(str, "%d", stageBest);
        loadttfScore(renderer, str, 390, y, 60, 30);

        sprintf(str, "%d", partieBest);
        loadttfScore(renderer, str, 500, y, 60, 30);

        loadttfScore(renderer, players[i].date, 570, y, 150, 30);

        y = y + 54;
    }
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

void getNbDiag(int level)
{
    switch (level-1)
    {
    case 1:
        stageBest = 1;
        partieBest = 1;
        break;
    case 2:
        stageBest = 1;
        partieBest = 2;
        break;
    case 3:
        stageBest = 1;
        partieBest = 3;
        break;
    case 4:
        stageBest = 1;
        partieBest = 4;
        break;
    case 5:
        stageBest = 1;
        partieBest = 5;
        break;
    case 6:
        stageBest = 2;
        partieBest = 1;
        break;
    case 7:
        stageBest = 2;
        partieBest = 2;
        break;
    case 8:
        stageBest = 2;
        partieBest = 3;
        break;
    case 9:
        stageBest = 2;
        partieBest = 4;
        break;
    case 10:
        stageBest = 2;
        partieBest = 5;
        break;

    case 11:
        stageBest = 3;
        partieBest = 1;
        break;
    case 12:
        stageBest = 3;
        partieBest = 2;
        break;
    case 13:
        stageBest = 3;
        partieBest = 3;
        break;
    case 14:
        stageBest = 3;
        partieBest = 4;
        break;
    case 15:
        stageBest = 3;
        partieBest = 5;
        break;
    default:
        stageBest = 3;
        partieBest = 5;
        break;
    }
}
