#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "sauv.h"
typedef struct culle
{
    int x;
    int y;
    int i;
    int j;
    int nb;

} culle;

void loadttf(SDL_Renderer *renderer, const char *text);
void drawMatrice(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50], int matExist);
void circle(SDL_Window* window, SDL_Renderer* renderer,int n,culle t[25], int tabExiste);
int checkInTabCircle(culle t[25], int mouseX, int mouseY, int m);
void home(SDL_Window* window, SDL_Renderer* renderer);
void quitJeu(SDL_Window* window,SDL_Renderer* renderer);
void playMusic();
int game(SDL_Window *window,SDL_Renderer* renderer,UserData player, int* isMute);
void getNbDiagN(int level);
#endif // GAME_H_INCLUDED
