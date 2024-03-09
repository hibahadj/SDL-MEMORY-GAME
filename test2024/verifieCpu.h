#ifndef VERIFIECPU_H_INCLUDED
#define VERIFIECPU_H_INCLUDED

typedef struct culle
{
    int x;
    int y;
    int i;
    int j;
    int nb;
} culle;

void desaineCpu(SDL_Renderer* renderer, SDL_Surface* imageSurface,int x,int y,int width,int height);
int verifieCpu(SDL_Window* window,SDL_Renderer* renderer, culle m[50][50], culle c[25],culle pointD,int n, int nbDiag, int numCirc, int* score);
void rotateImgCpu(SDL_Renderer* renderer, SDL_Surface* imageSurface, int x, int y, double angle);
void drawDiagMCpu(SDL_Window* window, SDL_Renderer* renderer, int n, culle matrice[50][50]);
int eventClickCpu (SDL_Window* window, SDL_Renderer* renderer, int* score, int scoreP);
#endif // VERIFIECPU_H_INCLUDED
