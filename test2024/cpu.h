#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED


void loadttfCpu(SDL_Renderer *renderer, const char *text);
void drawMatriceCpu(SDL_Window* window, SDL_Renderer* renderer, int n, culle Tab_matrice_flach[50][50], int matExist);
void circleCpu(SDL_Window* window, SDL_Renderer* renderer,int n,culle t[25], int tabExiste);
int checkInTabCircleCpu (culle t[25], int mouseX, int mouseY, int m);
void homeCpu(SDL_Window* window, SDL_Renderer* renderer);
void quitJeuCpu(SDL_Window* window,SDL_Renderer* renderer);
void playMusicCpu();
int cpu(SDL_Window *window,SDL_Renderer* renderer, int level, int* isMute);
void getNbDiagNCpu(int level);
#endif // CPU_H_INCLUDED
