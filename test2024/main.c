#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "input.h"
#include "menu.h"
#include "game.h"
#include "sauv.h"
#include "cpu.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window ;
SDL_Renderer* renderer;
int mute;


void closeSDLMain()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    char* inputText;
    int choixMenu=0;
    UserData player;
    mute = 0;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)!= 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Text Input in SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //player.name = input(window, renderer);
    strcpy(player.name,input(window, renderer));
    while (choixMenu !=5)
    {
        choixMenu = menu(window, renderer, &mute);
        switch (choixMenu)
        {
        case 1 ://new game
            player.level = -1;
            player = getData(player);
            game(window, renderer, player, &mute);
            bestScore(player);
            break;
        case 2://resume game
            player.level = 100;
            player = getData(player);
            game(window, renderer, player, &mute);
            bestScore(player);
            break;
        case 3:
            cpu(window, renderer, 1, &mute);
            break;
        case 4:
            //input(2);
            break;
        case 6:
            //Score();
            break;
        case 8:
            //HOW();
            break;
        }
    }
    closeSDLMain();
}

