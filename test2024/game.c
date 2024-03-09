#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "pause.h"
#include "verifie.h"
#include "sauv.h"

#define regtWeidth 80
#define regtHeight 80
#define circleWeidth 50
#define circleHeight 50
#define departX 230
#define departY 150

int nMat = 3;
int nbDiagMat = 2;
int score = 0, stage= 1, partie = 1;

Mix_Music* music = NULL;

typedef struct culle
{
    int x;
    int y;
    int i;
    int j;
    int nb;

} culle;

void loadttf(SDL_Renderer *renderer, const char *text)
{
    TTF_Font* font = TTF_OpenFont("font/Miglia.ttf", 100);
    if (!font)
    {
        printf("font not find! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Color color = {243, 138, 0, 255};
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

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_Rect recttitre = {10, 10, 400, 60};
    SDL_RenderCopy(renderer, texture, NULL, &recttitre);
    SDL_DestroyTexture(texture);
}

void drawMatrice(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50], int matExist)
{
    int i, j;
    int x = departX*4/n, y = departY*4/n;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(matExist == 0)
            {
                Tab_matrice_flach[i][j].x=x+j*regtWeidth;
                Tab_matrice_flach[i][j].y=y+i*regtHeight;
                Tab_matrice_flach[i][j].nb=0;
            }
            SDL_Surface* imageSurface = SDL_LoadBMP("image/pngwing.com-_21_.bmp");
            desaine(renderer,imageSurface,Tab_matrice_flach[i][j].x, Tab_matrice_flach[i][j].y,regtWeidth, regtHeight);
        }
    }
}

void circle(SDL_Window* window, SDL_Renderer* renderer,int n,culle t[25], int tabExiste)
{
    int dX= departX*4/n, dY= departY*4/n;
    int i,x,y;

    if(tabExiste == 0)
    {
        for (i = 0; i < n; i++)
        {
            //localiser les circle TOP
            x= dX+(80*i)+15;
            t[i].x=x;
            t[i].i=0;

            y= dY-50;
            t[i].y=y;
            t[i].j=i;
            //localiser les circle BOTTOM
            x= dX+(80*(n-i-1))+15;
            t[i+n*2].x=x;
            t[i+n*2].i=n-1;

            y= dY+(80*n);
            t[i+n*2].y=y;
            t[i+n*2].j=n-i-1;
            //localiser les circle RIGHT
            y=dY+(80*i)+15;
            t[i+n].y=y;
            t[i+n].j=n-1;

            x=dX+(80*n);
            t[i+n].x=x;
            t[i+n].i=i;
            //localiser les circle LEFT
            x=dX-50;
            t[i+n*3].x=x;
            t[i+n*3].i=n-i-1;

            y=dY+(80*(n-i-1))+15;
            t[i+n*3].y=y;
            t[i+n*3].j=0;
        }
    }

    for (i = 0; i < n*4; i++)
    {
        SDL_Surface* imageSurface = SDL_LoadBMP("image/pngwing.com-_22_.bmp");
        desaine(renderer, imageSurface, t[i].x, t[i].y, circleWeidth, circleHeight);
    }
}

int checkInTabCircle (culle t[25], int mouseX, int mouseY, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if(mouseX<=t[i].x+circleHeight && mouseX>=t[i].x && mouseY<=t[i].y+circleWeidth && mouseY>=t[i].y)
        {
            return i;
        }
    }
    return -1;
}

void drawDiag(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50],int nbDiag)
{
    int i=0, iDiag, jDiag, xDiag, yDiag;
    int etatDiag;//1:right 2:left
    int x = departX*4/n, y = departY*4/n;
    SDL_Surface* imageSurface;

    srand( time( NULL ) );
    while (i < nbDiag)
    {
        iDiag = rand() % n;
        jDiag = rand() % n;
        xDiag = x+jDiag*regtWeidth;
        yDiag = y+iDiag*regtHeight;
        etatDiag = rand() % 2;
        etatDiag = etatDiag+1;
        if(Tab_matrice_flach[iDiag][jDiag].nb == 0)
        {
            Tab_matrice_flach[iDiag][jDiag].nb = etatDiag;
            if (etatDiag == 2)
            {
                imageSurface = SDL_LoadBMP("image/pngwing.com-_18_.bmp");
            }
            else
            {
                imageSurface = SDL_LoadBMP("image/pngwing.com-_17_.bmp");
            }
            desaine(renderer, imageSurface, xDiag + 10,
                    yDiag + 15, 50, 50);
            i++;
        }
    }
}

void home(SDL_Window* window, SDL_Renderer* renderer)
{
    char str[12]="";
    char txtHeasder[30]="";
    //HOME
    SDL_Surface* imageSurface = SDL_LoadBMP("image/home.bmp");
    desaine(renderer, imageSurface, 750,30,40,40);
    //PAUSE
    imageSurface = SDL_LoadBMP("image/bPause.bmp");
    desaine(renderer, imageSurface, 750,80,40,40);
    //afficher stage partie et score
    strcat(txtHeasder, "Stage: ");
    sprintf(str, "%d", stage);
    strcat(txtHeasder, str);
    strcat(txtHeasder, "   Partie: ");
    sprintf(str, "%d", partie);
    strcat(txtHeasder, str);
    strcat(txtHeasder, "   Score: ");
    sprintf(str, "%d", score);
    //strcat(txtHeasder, str);
    loadttf(renderer, txtHeasder);
}

int jeu(SDL_Window* window,SDL_Renderer* renderer,int n,int nbF,culle Tab_flache[50][50], int* isMute)
{
    culle t[25];//save positios des circles
    int nb_circle=4*n, RdC, circleClick;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //set background
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 70);
    SDL_RenderClear(renderer);
    //init le jeu
    drawMatrice(window, renderer, n, Tab_flache,0);
    circle (window,renderer,n,t,0);
    home(window,renderer);
    //SDL_RenderPresent(renderer);
    drawDiag(window, renderer, n, Tab_flache,nbF);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    // Get the initial time
    //Uint32 startTime = SDL_GetTicks();
    //Uint32 targetTime = startTime + 3000;  // 3 seconds

    // Main loop
    //while (SDL_GetTicks() < targetTime) {
    //usleep(30);
    SDL_DestroyRenderer(renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 70);
    SDL_RenderClear(renderer);
    drawMatrice(window, renderer, n, Tab_flache, 1);
    circle (window,renderer,n,t,1);
    home(window,renderer);
    SDL_RenderPresent(renderer);
    //draw yellow init circule
    srand(time(NULL));
    RdC=rand()%nb_circle;
    SDL_Surface* imageSurface = SDL_LoadBMP("image/circle_yellow.bmp");
    if (!imageSurface)
    {
        printf("IMG_Load Error: %s\n", SDL_GetError());
        quitJeu(window,renderer);
    }
    desaine(renderer, imageSurface,t[RdC].x,t[RdC].y,circleWeidth,circleHeight);
    SDL_RenderPresent(renderer);
    //click listener
    int quit = 0;
    while (quit == 0)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP)
            {
                circleClick= checkInTabCircle(t, e.button.x, e.button.y, nb_circle);
                if(circleClick !=-1)
                {
                    quit = 2;
                }
                else
                {
                    if(e.button.x<=790 && e.button.x>=750 && e.button.y<=70 && e.button.y>=30)
                    {
                        printf("Home\n");
                        quit = 4;
                    }

                    if(e.button.x<=790 && e.button.x>=750 && e.button.y<=120 && e.button.y>=80)
                    {
                        printf("PAUSE\n");
                        if(*isMute != 1)
                            Mix_PauseMusic();
                        SDL_DestroyRenderer(renderer);
                        quit=paused(window,renderer);
                        if(quit != 4 && *isMute != 1)
                        {
                            Mix_ResumeMusic();
                        }
                        if(quit == 0 )
                        {
                            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                            SDL_SetRenderDrawColor(renderer, 60, 60, 60, 60);
                            SDL_RenderClear(renderer);
                            drawMatrice(window, renderer, n, Tab_flache, 1);
                            circle (window,renderer,n,t,1);
                            home(window,renderer);
                            SDL_Surface* imageSurface = SDL_LoadBMP("image/circle_yellow.bmp");
                            desaine(renderer, imageSurface,t[RdC].x,t[RdC].y,circleWeidth,circleHeight);
                            SDL_RenderPresent(renderer);
                        }


                    }
                }
            }
        }
        // Check for keyboard events
        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Esc key pressed\n");
                quit = 4;
            }
        }
    }

    switch (quit)
    {
    case 1://quiter le jeu
        quitJeu(window, renderer);
        break;
    case 2://click red circle player
        imageSurface = SDL_LoadBMP("image/circle_red.bmp");
        desaine(renderer, imageSurface,t[circleClick].x,t[circleClick].y,circleWeidth,circleHeight);
        SDL_RenderPresent(renderer);
        int isWin = 0;
        renderer = verifie(window,renderer, Tab_flache, t,t[RdC], t[circleClick],n, nbF, RdC, circleClick, &score, &isWin);
        SDL_DestroyRenderer(renderer);
        return isWin;
        break;
    case 3://replay
        SDL_DestroyRenderer(renderer);
        return quit;
        break;
    case 4:// click button home
        SDL_DestroyRenderer(renderer);
        break;
    }

    return 0;
}

void quitJeu(SDL_Window* window,SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Function to play music
void playMusic()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
    }

    music = Mix_LoadMUS("audio/play1.mp3");
    if (!music)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
    }

}

int game(SDL_Window *window,SDL_Renderer* renderer,UserData player, int* isMute)
{
    int k=3;
    culle Tab_matrice_flach[50][50];

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        quitJeu(window, renderer);
        return 1;
    }

    if(*isMute != 1)
    {
        playMusic();
        if (Mix_PlayMusic(music, -1) == -1)
        {
            fprintf(stderr, "Mix_PlayMusic Error: %s\n", Mix_GetError());
            Mix_FreeMusic(music);
            Mix_CloseAudio();
        }
    }

    score = player.score;
    getNbDiagN(player.level);
    while(k==3)
    {
        k = jeu(window, renderer, nMat, nbDiagMat, Tab_matrice_flach, isMute);
        if(k==20)
        {
            player.score = score;
            player.level=player.level+1;
            writeData(player);
            getNbDiagN(player.level);

            if(player.level<=15)
            {
                k=3;
            }
            else
            {
                SDL_DestroyRenderer(renderer);
                afficherWon(window, renderer, score, 0);
            }

        }
    }
    if(*isMute != 1)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }
    return 0;
}

void getNbDiagN(int level)
{
    switch (level)
    {
    case 1:
        nMat = 3;
        nbDiagMat = 3;
        stage = 1;
        partie = 1;
        break;
    case 2:
        nMat = 3;
        nbDiagMat = 4;
        stage = 1;
        partie = 2;
        break;
    case 3:
        nMat = 3;
        nbDiagMat = 5;
        stage = 1;
        partie = 3;
        break;
    case 4:
        nMat = 3;
        nbDiagMat = 6;
        stage = 1;
        partie = 4;
        break;
    case 5:
        nMat = 3;
        nbDiagMat = 7;
        stage = 1;
        partie = 5;
        break;

    case 6:
        nMat = 4;
        nbDiagMat = 7;
        stage = 2;
        partie = 1;
        break;
    case 7:
        nMat = 4;
        nbDiagMat = 8;
        stage = 2;
        partie = 2;
        break;
    case 8:
        nMat = 4;
        nbDiagMat = 9;
        stage = 2;
        partie = 3;
        break;
    case 9:
        nMat = 4;
        nbDiagMat = 10;
        stage = 2;
        partie = 4;
        break;
    case 10:
        nMat = 4;
        nbDiagMat = 11;
        stage = 2;
        partie = 5;
        break;

    case 11:
        nMat = 5;
        nbDiagMat = 11;
        stage = 3;
        partie = 1;
        break;
    case 12:
        nMat = 5;
        nbDiagMat = 12;
        stage = 3;
        partie = 2;
        break;
    case 13:
        nMat = 5;
        nbDiagMat = 13;
        stage = 3;
        partie = 3;
        break;
    case 14:
        nMat = 5;
        nbDiagMat = 14;
        stage = 3;
        partie = 4;
        break;
    case 15:
        nMat = 5;
        nbDiagMat = 15;
        stage = 3;
        partie = 5;
        break;
    default:
        nMat = 5;
        nbDiagMat = 15;
        stage = 3;
        partie = 5;
        break;
    }
}
