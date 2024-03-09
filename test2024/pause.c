#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int pause(SDL_Window *window,SDL_Renderer* renderer)
{
    SDL_Surface *menu = SDL_LoadBMP("image/PAUSE.bmp");
    SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_RenderCopy(renderer, txt, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = -1;
    while (quit == -1)
    {
        while (SDL_PollEvent(&event)!= 0)
        {
            int x1, y1;

            x1 = event.motion.x;
            y1 = event.motion.y;

            if(event.type == SDL_QUIT)
            {

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }

            if (event.type == SDL_MOUSEBUTTONUP && x1 <= 372 && x1 >= 293 && y1 <= 319 && y1 >= 261)
            {
                printf("resume\n");
                quit = 0;
            }
            if (event.type == SDL_MOUSEBUTTONUP && x1 <= 512 && x1 >= 425 && y1 <= 321 && y1 >= 265)
            {
                playMusic();
                printf("replay\n");
                quit = 3;
            }
            if (event.type == SDL_MOUSEBUTTONUP && x1 <= 512 && x1 >= 293 && y1 <= 400 && y1 >= 344)
            {
                printf("HOME\n");
                quit = 4;
            }
        }
                // Check for keyboard events
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Esc cpu key pressed\n");
                quit = 4;
            }
        }
    }
    // Release resources
    SDL_DestroyTexture(txt);
    SDL_FreeSurface(menu);
    return quit;
}

int paused(SDL_Window* window,SDL_Renderer* renderer)
{
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    int result = pause(window, renderer);
    SDL_DestroyRenderer(renderer);
    return result;
}
