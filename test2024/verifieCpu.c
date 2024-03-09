#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ma_bibliot.h"
#include "verifieCpu.h"

#define regtWH 80
#define circleWH 50
#define circleButton 60


Liste tete,prd;


int verifieCpu(SDL_Window* window,SDL_Renderer* renderer, culle m[50][50], culle c[25],culle pointD,int n, int nbDiag, int numCirc, int* score)
{
    int i,j,dist,numCircCorr;
    int end = 0, nb_circle=4*n, unit= 5*(n-2);
    int scoreP = unit*nbDiag;// score Partie
    SDL_Surface* imageSurface;
    path initP ;
    culle pointF;

    if (numCirc < n)
    {
        dist = 1;//top
    }
    else if (numCirc < n*2)
    {
        dist = 2;//right
    }
    else if (numCirc < n*3)
    {
        dist = 3;//bootom
    }
    else
    {
        dist = 4;//left
    }

    i=pointD.i;
    j=pointD.j;
    initP.x= pointD.x;
    initP.y= pointD.y;
    tete = NULL;
    ajout_tete(&tete,initP);
    prd = tete;

    while(end == 0)
    {
        initP.x= m[i][j].x;
        initP.y= m[i][j].y;

        switch (dist)
        {
        case 1 ://top
            switch (m[i][j].nb)
            {
            case 0 ://=
                if(i==n-1)
                {
                    end=1;
                    numCircCorr = n*3-j-1;
                }
                else
                {
                    i=i+1;
                }
                initP.rotImg=1.0;
                break;
            case 1:
                if(j==n-1)
                {
                    end=1;
                    numCircCorr = n+i;
                }
                else
                {
                    j=j+1;
                    dist= 4;
                }
                initP.rotImg=0.0;
                scoreP = scoreP+unit;
                break;
            case 2://
                if(j==0)
                {
                    end=1;
                    numCircCorr = n*4-i-1;
                }
                else
                {
                    j=j-1;
                    dist=2;
                }
                initP.rotImg=270.0;
                scoreP = scoreP+unit;
                break;
            }
            break;
        case 2://right
            switch (m[i][j].nb)
            {
            case 0 ://=
                if(j==0)
                {
                    end=1;
                    numCircCorr = n*4-i-1;
                }
                else
                {
                    j=j-1;
                }
                initP.rotImg=2.0;
                break;
            case 1:
                if(i==0)
                {
                    end=1;
                    numCircCorr = j;
                }
                else
                {
                    i=i-1;
                    dist = 3;
                }
                initP.rotImg=0.0;
                scoreP = scoreP+unit;
                break;
            case 2://
                if(i==n-1)
                {
                    end=1;
                    numCircCorr = n*3-j-1;
                }
                else
                {
                    i=i+1;
                    dist = 1;
                }
                initP.rotImg=90.0;
                scoreP = scoreP+unit;
                break;
            }
            break;
        case 3://bottom
            switch (m[i][j].nb)
            {
            case 0 :
                if(i==0)
                {
                    end=1;
                    numCircCorr = j;
                }
                else
                {
                    i=i-1;
                }
                initP.rotImg=1.0;
                break;
            case 1:
                if(j==0)
                {
                    end=1;
                    numCircCorr = n*4-i-1;
                }
                else
                {
                    j=j-1;
                    dist=2;
                }
                initP.rotImg=180.0;
                scoreP = scoreP+unit;
                break;
            case 2:
                if(j==n-1)
                {
                    end=1;
                    numCircCorr = n+i;
                }
                else
                {
                    j=j+1;
                    dist= 4;
                }
                initP.rotImg=90.0;
                scoreP = scoreP+unit;
                break;
            }
            break;
        case 4://left
            switch (m[i][j].nb)
            {
            case 0 :
                if(j==n-1)
                {
                    end=1;
                    numCircCorr = n+i;
                }
                else
                {
                    j=j+1;
                }
                initP.rotImg=2.0;
                break;
            case 1:
                if(i==n-1)
                {
                    end=1;
                    numCircCorr = n*3-j-1;
                }
                else
                {
                    i=i+1;
                    dist = 1;
                }
                initP.rotImg=180.0;
                scoreP = scoreP+unit;
                break;
            case 2:
                if(i==0)
                {
                    end=1;
                    numCircCorr = j;
                }
                else
                {
                    i=i-1;
                    dist = 3;
                }
                initP.rotImg=270.0;
                scoreP = scoreP+unit;
                break;
            }
            break;
        }

        ajout_apres(&prd, initP);
    }

    supprimer_tete(&tete);

    pointF.i = i;
    pointF.j = j;
    pointF.x = c[numCircCorr].x;
    pointF.y = c[numCircCorr].y;

    imageSurface = SDL_LoadBMP("image/circle_red.bmp");
    desaineCpu(renderer, imageSurface, pointF.x, pointF.y, circleWH, circleWH);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    //affiche_liste(tete);
    drawDiagMCpu(window,renderer, n, m);
    SDL_RenderPresent(renderer);
    //SDL_Surface* imageSurface;
    while(tete != NULL)
    {
        if (tete->inf.rotImg == 1.0)
        {
            imageSurface = SDL_LoadBMP("image/ver1.bmp");
            if (!imageSurface)
            {
                printf("IMG_Load Error: %s\n", SDL_GetError());
                quitJeuCpu(window,renderer);
            }
            desaineCpu(renderer, imageSurface, tete->inf.x, tete->inf.y, regtWH, regtWH);
        }
        else if (tete->inf.rotImg == 2.0)
        {
            imageSurface = SDL_LoadBMP("image/hor2.bmp");
            if (!imageSurface)
            {
                printf("IMG_Load Error: %s\n", SDL_GetError());
                quitJeuCpu(window,renderer);
            }
            desaineCpu(renderer, imageSurface, tete->inf.x, tete->inf.y, regtWH, regtWH);
        }
        else
        {
            imageSurface = SDL_LoadBMP("image/rotat0.bmp");
            if (!imageSurface)
            {
                printf("IMG_Load Error: %s\n", SDL_GetError());
                quitJeuCpu(window,renderer);
            }
            rotateImgCpu(renderer, imageSurface, tete->inf.x, tete->inf.y, tete->inf.rotImg);
        }
        SDL_RenderPresent(renderer);
        tete=tete->svt;

    }

    imageSurface = SDL_LoadBMP("image/circle_green.bmp");
    if (!imageSurface)
    {
        printf("IMG_Load Error: %s\n", SDL_GetError());
        quitJeuCpu(window,renderer);
    }
    desaineCpu(renderer, imageSurface, pointF.x, pointF.y, circleWH, circleWH);
    SDL_RenderPresent(renderer);

    imageSurface = SDL_LoadBMP("image/replay.bmp");
    desaineCpu(renderer, imageSurface, 650, 520, circleButton, circleButton);
    imageSurface = SDL_LoadBMP("image/next.bmp");
    desaineCpu(renderer, imageSurface, 720, 520, circleButton, circleButton);
    //HOME
    imageSurface = SDL_LoadBMP("image/home.bmp");
    desaineCpu(renderer, imageSurface, 750,30,40,40);

    SDL_RenderPresent(renderer);

    free(tete);
    int quit = eventClickCpu(window, renderer, score, scoreP);

    return quit;
}

void desaineCpu(SDL_Renderer* renderer, SDL_Surface* imageSurface,int x,int y,int width,int height)
{
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    SDL_Rect destination = {x,y, width, height};
    SDL_RenderCopy(renderer, imageTexture, NULL, &destination);
    SDL_DestroyTexture(imageTexture);
}

void rotateImgCpu(SDL_Renderer* renderer, SDL_Surface* imageSurface, int x, int y, double angle)
{
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    SDL_Rect dstRect = {x, y, regtWH, regtWH};
    SDL_RenderCopyEx(renderer, imageTexture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
    if (SDL_RenderCopyEx(renderer, imageTexture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE) != 0)
    {
        printf("Failed to render texture: %s\n", SDL_GetError());
    }
    SDL_DestroyTexture(imageTexture);
}

void drawDiagMCpu(SDL_Window* window, SDL_Renderer* renderer, int n, culle matrice[50][50])
{
    int i, j;
    SDL_Surface* imageSurface;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrice[i][j].nb == 2)
            {
                imageSurface = SDL_LoadBMP("image/pngwing.com-_18_.bmp");
                desaineCpu(renderer, imageSurface, matrice[i][j].x + 10,
                           matrice[i][j].y + 15, 50, 50);
            }
            if (matrice[i][j].nb == 1)
            {
                imageSurface = SDL_LoadBMP("image/pngwing.com-_17_.bmp");
                desaineCpu(renderer, imageSurface, matrice[i][j].x + 10,
                           matrice[i][j].y + 15, 50, 50);
            }

        }
    }
}

int eventClickCpu (SDL_Window* window, SDL_Renderer* renderer, int* score, int scoreP)
{
    int quit = 0;
    SDL_Event e;
    while (quit == 0)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quitJeuCpu(window,renderer);
                return 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP)
            {
                if(e.button.x<=710 && e.button.x>=650 && e.button.y<=580 && e.button.y>=520)
                {
                    printf("reply\n");
                    quit = 3;
                }
                if(e.button.x<=780 && e.button.x>=720 && e.button.y<=580 && e.button.y>=520)
                {
                    *score = *score+ scoreP;
                    quit = 20;
                }

                if(e.button.x<=790 && e.button.x>=750 && e.button.y<=70 && e.button.y>=30)
                {
                    printf("Home\n");
                    quit = 4;
                }
            }
        }

        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_LEFT)
            {
                printf("reply\n");
                quit = 3;
            }
        }

        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_RIGHT)
            {
                *score = *score+ scoreP;
                quit = 20;
            }
        }

        // Check for keyboard events
        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                printf("Esc cpu key pressed\n");
                quit = 4;
            }
        }
    }
    return quit;
}
