#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Texture* gTextTexture = NULL;
SDL_Rect gTextBoxRect = {100, 100, 200, 150};
SDL_bool gTextInput = SDL_FALSE;
char gTextInputText[15] = "";

void closeSDL(SDL_Window *window,SDL_Renderer* renderer,TTF_Font* font)
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(gTextTexture);
    SDL_DestroyRenderer(renderer);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
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

    SDL_FreeSurface(textSurface);
    return texture;
}

char* input(SDL_Window *window,SDL_Renderer* renderer)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return ;
    }
    SDL_Surface *inputImg = SDL_LoadBMP("image/input.bmp");
    gTextTexture = SDL_CreateTextureFromSurface(renderer, inputImg);
    SDL_RenderCopy(renderer, gTextTexture, NULL, NULL);
    SDL_DestroyTexture(gTextTexture);
    SDL_FreeSurface(inputImg);
    SDL_RenderPresent(renderer);

    // Load font
    TTF_Font* font = TTF_OpenFont("font/Miglia.ttf", 40);
    if (font == NULL)
    {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return ;
    }

    SDL_Color textColor = { 0, 0, 0, 255 }; // Black color

    // Main loop
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = SDL_TRUE;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    if(strlen(gTextInputText)>0)
                    {
                        closeSDL(window, renderer, font);
                        quit = SDL_TRUE;
                        return gTextInputText;
                    }
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(gTextInputText) > 0)
                {
                    // User pressed Backspace, remove the last character
                    gTextInputText[strlen(gTextInputText) - 1] = '\0';
                    gTextInput = SDL_TRUE;
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                // Handle text input events
                if(strlen(gTextInputText)<15)
                {
                    strcat(gTextInputText, e.text.text);
                    gTextInput = SDL_TRUE;
                }
            }
        }
        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Esc quit key pressed\n");
                quit = SDL_TRUE;
            }
        }

        // Render text
        if(gTextInput)
        {
            SDL_DestroyRenderer(renderer);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_Surface *inputImg = SDL_LoadBMP("image/input.bmp");
            gTextTexture = SDL_CreateTextureFromSurface(renderer, inputImg);
            SDL_RenderCopy(renderer, gTextTexture, NULL, NULL);
            SDL_DestroyTexture(gTextTexture);
            SDL_FreeSurface(inputImg);
            if(strlen(gTextInputText)>0)
            {
                gTextTexture = loadTexture(renderer, gTextInputText, font, textColor);
                if (gTextTexture != NULL)
                {
                    //get width and height of input text
                    SDL_QueryTexture(gTextTexture, NULL, NULL, &gTextBoxRect.w, &gTextBoxRect.h);
                    gTextBoxRect.x = (WINDOW_WIDTH - gTextBoxRect.w) / 2;
                    gTextBoxRect.y = (WINDOW_HEIGHT - gTextBoxRect.h) / 2;
                    SDL_RenderCopy(renderer, gTextTexture, NULL, &gTextBoxRect);
                    SDL_DestroyTexture(gTextTexture);
                }
            }
            SDL_RenderPresent(renderer);
            gTextInput = SDL_FALSE;
        }
    }
    return 0;
}
