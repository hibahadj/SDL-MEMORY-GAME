#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "verifieCpu.h"
#include "won.h"

#define regtWeidth 80
#define regtHeight 80
#define circleWeidth 50
#define circleHeight 50
#define departX 230
#define departY 150

int nMatCpu = 3;
int nbDiagMatCpu = 2;
int scoreCpu = 0, stageCpu= 1, partieCpu = 1;

Mix_Music* musicCpu = NULL;



void loadttfCpu(SDL_Renderer *renderer, const char *text)
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

void drawMatriceCpu(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50], int matExist)
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
            desaineCpu(renderer,imageSurface,Tab_matrice_flach[i][j].x, Tab_matrice_flach[i][j].y,regtWeidth, regtHeight);
        }
    }
}

void circleCpu(SDL_Window* window, SDL_Renderer* renderer,int n,culle t[25], int tabExiste)
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
        desaineCpu(renderer, imageSurface, t[i].x, t[i].y, circleWeidth, circleHeight);
    }
}

int checkInTabCircleCpu (culle t[25], int mouseX, int mouseY, int m)
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

void drawDiagCpu(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50],int nbDiag)
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
            desaineCpu(renderer, imageSurface, xDiag + 10,
                       yDiag + 15, 50, 50);
            i++;
        }
    }
}

void homeCpu(SDL_Window* window, SDL_Renderer* renderer)
{
    char str[12]="";
    char txtHeasder[30]="";

    //afficher stageCpu partieCpu et scoreCpu
    strcat(txtHeasder, "stage: ");
    sprintf(str, "%d", stageCpu);
    strcat(txtHeasder, str);
    strcat(txtHeasder, "   partie: ");
    sprintf(str, "%d", partieCpu);
    strcat(txtHeasder, str);
    strcat(txtHeasder, "   score: ");
    sprintf(str, "%d", scoreCpu);
    //strcat(txtHeasder, str);
    loadttfCpu(renderer, txtHeasder);
}

int jeuCpu(SDL_Window* window,SDL_Renderer* renderer,int n,int nbF,culle Tab_flache[50][50], int* isMute)
{
    culle t[25];//save positions des circles
    int nb_circle=4*n, RdC, circleClick;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //set background
    SDL_SetRenderDrawColor(renderer, 35, 65, 140, 255);
    SDL_RenderClear(renderer);
    //init le jeu
    drawMatriceCpu(window, renderer, n, Tab_flache,0);
    circleCpu (window,renderer,n,t,0);
    homeCpu(window,renderer);
    drawDiagCpu(window, renderer, n, Tab_flache,nbF);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 35, 65, 140, 255);
    SDL_RenderClear(renderer);
    drawMatriceCpu(window, renderer, n, Tab_flache, 1);
    circleCpu (window,renderer,n,t,1);
    homeCpu(window,renderer);
    SDL_RenderPresent(renderer);
    //draw yellow init circule
    srand(time(NULL));
    RdC=rand()%nb_circle;
    SDL_Surface* imageSurface = SDL_LoadBMP("image/circle_yellow.bmp");
    if (!imageSurface)
    {
        printf("IMG_Load Error: %s\n", SDL_GetError());
        quitJeuCpu(window,renderer);
    }
    desaineCpu(renderer, imageSurface,t[RdC].x,t[RdC].y,circleWeidth,circleHeight);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    int quit = verifieCpu(window,renderer, Tab_flache, t,t[RdC],n, nbF, RdC, &scoreCpu);

    SDL_DestroyRenderer(renderer);
    return quit;
}

void quitJeuCpu(SDL_Window* window,SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Function to play music
void playMusicCpu()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
    }

    musicCpu = Mix_LoadMUS("audio/play2.mp3");
    if (!musicCpu)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
    }
}

int cpu(SDL_Window *window,SDL_Renderer* renderer, int level, int* isMute)
{
    int k=3;
    culle Tab_matrice_flach[50][50];
    scoreCpu = 0;

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        quitJeuCpu(window, renderer);
        return 1;
    }

    if(*isMute != 1)
    {
        playMusicCpu();
        if (Mix_PlayMusic(musicCpu, -1) == -1)
        {
            fprintf(stderr, "Mix_PlayMusic Error: %s\n", Mix_GetError());
            Mix_FreeMusic(musicCpu);
            Mix_CloseAudio();
        }
    }


    getNbDiagNCpu(level);
    while(k==3)
    {
        k = jeuCpu(window, renderer, nMatCpu, nbDiagMatCpu, Tab_matrice_flach, isMute);
        if(k==20)
        {
            level=level+1;
            getNbDiagNCpu(level);
            if(level<=15)
            {
                k=3;
            }
            else
            {
                SDL_DestroyRenderer(renderer);
                afficherWon(window, renderer, scoreCpu, 1);
            }
        }
    }
    if(*isMute != 1)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musicCpu);
        Mix_CloseAudio();
    }
    return 0;
}

void getNbDiagNCpu(int level)
{
    switch (level)
    {
    case 1:
        nMatCpu = 3;
        nbDiagMatCpu = 3;
        stageCpu = 1;
        partieCpu = 1;
        break;
    case 2:
        nMatCpu = 3;
        nbDiagMatCpu = 4;
        stageCpu = 1;
        partieCpu = 2;
        break;
    case 3:
        nMatCpu = 3;
        nbDiagMatCpu = 5;
        stageCpu = 1;
        partieCpu = 3;
        break;
    case 4:
        nMatCpu = 3;
        nbDiagMatCpu = 6;
        stageCpu = 1;
        partieCpu = 4;
        break;
    case 5:
        nMatCpu = 3;
        nbDiagMatCpu = 7;
        stageCpu = 1;
        partieCpu = 5;
        break;

    case 6:
        nMatCpu = 4;
        nbDiagMatCpu = 7;
        stageCpu = 2;
        partieCpu = 1;
        break;
    case 7:
        nMatCpu = 4;
        nbDiagMatCpu = 8;
        stageCpu = 2;
        partieCpu = 2;
        break;
    case 8:
        nMatCpu = 4;
        nbDiagMatCpu = 9;
        stageCpu = 2;
        partieCpu = 3;
        break;
    case 9:
        nMatCpu = 4;
        nbDiagMatCpu = 10;
        stageCpu = 2;
        partieCpu = 4;
        break;
    case 10:
        nMatCpu = 4;
        nbDiagMatCpu = 11;
        stageCpu = 2;
        partieCpu = 5;
        break;

    case 11:
        nMatCpu = 5;
        nbDiagMatCpu = 11;
        stageCpu = 3;
        partieCpu = 1;
        break;
    case 12:
        nMatCpu = 5;
        nbDiagMatCpu = 12;
        stageCpu = 3;
        partieCpu = 2;
        break;
    case 13:
        nMatCpu = 5;
        nbDiagMatCpu = 13;
        stageCpu = 3;
        partieCpu = 3;
        break;
    case 14:
        nMatCpu = 5;
        nbDiagMatCpu = 14;
        stageCpu = 3;
        partieCpu = 4;
        break;
    case 15:
        nMatCpu = 5;
        nbDiagMatCpu = 15;
        stageCpu = 3;
        partieCpu = 5;
        break;
    default:
        nMatCpu = 5;
        nbDiagMatCpu = 15;
        stageCpu = 3;
        partieCpu = 5;
        break;
    }
}
