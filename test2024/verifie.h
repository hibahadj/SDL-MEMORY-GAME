#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

typedef struct culle
{
    int x;
    int y;
    int i;
    int j;
    int nb;
} culle;


void desaine(SDL_Renderer* renderer, SDL_Surface* imageSurface,int x,int y,int width,int height);
int eventClick (SDL_Window* window, SDL_Renderer* renderer, int bWin, int* score, int scoreP);
void drawDiagM(SDL_Window* window, SDL_Renderer* renderer, int n, culle matrice[50][50]);
void rotateImg(SDL_Renderer* renderer, SDL_Surface* imageSurface, int x, int y, double angle);
void desaine(SDL_Renderer* renderer, SDL_Surface* imageSurface,int x,int y,int width,int height);
SDL_Renderer* verifie(SDL_Window* window,SDL_Renderer* renderer, culle m[50][50], culle c[25],culle pointD, culle clickPly,int n, int nbDiag, int numCirc, int numCircClick, int* score, int* isWin);
#endif // PAUSE_H_INCLUDED
