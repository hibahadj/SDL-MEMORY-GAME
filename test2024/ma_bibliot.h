#ifndef MA_BIBLIOT_H_INCLUDED
#define MA_BIBLIOT_H_INCLUDED

typedef struct path
{
    int x;
    int y;
    double rotImg;
} path;


typedef struct cellule *Liste;
typedef struct cellule
{
    path inf;
    Liste svt;
}cellule;


void ajout_tete(Liste *t, path e);
void affiche_liste(Liste t);

void ajout_apres(Liste *prd, path e);
void supprimer_tete(Liste *t);
void supprimer_apres(Liste *prd);
#endif // MA_BIBLIOT_H_INCLUDED
