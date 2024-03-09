#include "ma_bibliot.h"
#include <stdio.h>
#include <stdlib.h>

void ajout_tete(Liste *t, path e)
{
    Liste nouv;

    nouv=(Liste) malloc(sizeof(cellule));

    if (nouv==NULL)
    {
         printf("erreur memoire saturee");
         exit(-1);  // arrete le prog
    }

    nouv ->inf = e;
    nouv ->svt = *t;
    *t = nouv;
}

void affiche_liste(Liste t)
{
    while(t != NULL)
    {
       printf("x=%d, y=%d , rotat=%f\n", t->inf.x,t->inf.y,t->inf.rotImg);
       t=t->svt;
    }
}

void ajout_apres(Liste *prd, path e)
{
    Liste nouv;
    nouv=(Liste) malloc(sizeof(cellule));
    if (nouv==NULL)
    {
         printf("erreur memoire saturee");
         exit(-1);  // arrete le prog
    }

    nouv ->inf = e;
    nouv ->svt = (*prd)->svt;
    (*prd)->svt = nouv;
    *prd = nouv; // optionnelle
}


void supprimer_tete(Liste *t)
{
    Liste tmp = *t;

    *t = (*t)->svt;
    free(tmp);
}

void supprimer_apres(Liste *prd)
{
    Liste temp;

    temp = (*prd)->svt;
    (*prd)->svt = temp->svt;

    *prd = (*prd)->svt;
    free(temp);
}

