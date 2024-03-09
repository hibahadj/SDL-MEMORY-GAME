#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

void how(SDL_Window *window,SDL_Renderer* renderer)
{
    SDL_Surface *menu = SDL_LoadBMP("image/how-to-play.bmp");
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_FreeSurface(menu);
    SDL_RenderCopy(renderer, txt, NULL, NULL);
    SDL_DestroyTexture(txt);
}

void closeSDLHow(SDL_Window *window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void howp(SDL_Window* window,SDL_Renderer* renderer)
{
    int running = 1;

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

    how(window, renderer);
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
                closeSDLHow(window, renderer);
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

