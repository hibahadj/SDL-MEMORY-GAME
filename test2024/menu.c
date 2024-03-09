#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#include "how.h"
#include "score.h"

Mix_Music* musicMenu = NULL;

void showMenu(SDL_Renderer* renderer, char url[20])
{
    SDL_Surface *menu=SDL_LoadBMP(url);
    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,menu);
    SDL_FreeSurface(menu);
    SDL_RenderCopy(renderer, txt, NULL, NULL);
    SDL_DestroyTexture(txt);
    SDL_RenderPresent(renderer);
}

void closeSDLMenu(SDL_Window *window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void playMusicMenu()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
    }

    musicMenu = Mix_LoadMUS("audio/play.mp3");
    if (!musicMenu)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
    }
}

int menu(SDL_Window *window,SDL_Renderer* renderer, int* mute)
{
    bool running = true;
    bool isMute;
    int quit = -1;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    playMusicMenu();

    if(*mute == 0)
    {
        showMenu(renderer,"image/menu.bmp");
        isMute = true;
        if (Mix_PlayMusic(musicMenu, -1) == -1)
        {
            fprintf(stderr, "Mix_PlayMusic Error: %s\n", Mix_GetError());
            Mix_FreeMusic(musicMenu);
            Mix_CloseAudio();
        }
    }
    else
    {
        showMenu(renderer,"image/menu-mute.bmp");
        isMute = false;
    }

    SDL_Event event;
    while(quit==-1)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            int x1,y1;
            x1=event.motion.x;
            y1=event.motion.y;

            if(event.type == SDL_QUIT)
            {
                quit = 0;
                closeSDLMenu(window, renderer);
            }
            //play button
            if(event.type== SDL_MOUSEBUTTONUP)
            {
                if(x1<=389 && x1>=250 && y1<=180 && y1>=125)
                {
                    printf("start the game !\n");
                    SDL_DestroyRenderer(renderer);
                    quit = 1;
                }
                //continue play
                if(x1<=550 && x1>=411 && y1<=180 && y1>=125)
                {
                    printf("resume the game !\n");
                    SDL_DestroyRenderer(renderer);
                    quit = 2;
                }
                //cpu play bytton
                if(x1<=550 && x1>=250 && y1<=262 && y1>=207)
                {
                    printf("cpu start the game !\n");
                    SDL_DestroyRenderer(renderer);
                    quit = 3;
                }
                //score
                if(x1<=550 && x1>=250 && y1<=420 && y1>=365)
                {
                    printf("score !\n");
                    SDL_DestroyRenderer(renderer);
                    afficherBest(window,renderer);
                    quit = 7;
                }
                //exit button
                if(x1<=550 && x1>=250 && y1<=500 && y1>=445)
                {
                    printf("exit");
                    SDL_DestroyRenderer(renderer);
                    quit = 5;
                }
                //boutton mute
                if(x1<=714 && x1>=673 && y1<=70 && y1>=30)
                {
                    SDL_DestroyRenderer(renderer);
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                    if(isMute)
                    {
                        printf("mute music !\n");
                        showMenu(renderer,"image/menu-mute.bmp");
                        isMute = false;
                        *mute = 1;
                        Mix_HaltMusic();
                    }
                    else
                    {
                        printf("play music !\n");
                        showMenu(renderer,"image/menu.bmp");
                        if (Mix_PlayMusic(musicMenu, -1) == -1)
                        {
                            fprintf(stderr, "Mix_PlayMusic Error: %s\n", Mix_GetError());
                            Mix_FreeMusic(musicMenu);
                            Mix_CloseAudio();
                        }
                        isMute = true;
                        *mute = 0;
                    }
                }
                //boutton how to play
                if(x1<=768 && x1>=725 && y1<=70 && y1>=30)
                {
                    printf("how to play!\n");
                    SDL_DestroyRenderer(renderer);
                    howp(window,renderer);
                    quit = 6;
                }
            }
        }

        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Esc quit key pressed\n");
                quit = 5;
            }
        }

    }
    Mix_HaltMusic();
    Mix_FreeMusic(musicMenu);
    Mix_CloseAudio();
    return quit;
}
