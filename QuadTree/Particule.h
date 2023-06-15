#ifndef PARTICULE_H
#define PARTICULE_H

typedef struct particule {
    int x;
    int y;
} Particule, Point;

Particule cree_particule(int x, int y);

void generer_particule(Particule *tab_particule, int nb_particule, int w);

void generer_direction(int tab_direction[], int nb_particule);

void deplacer_particule(Particule *tab_particule, int tab_direction[], int nb_particule, int frame, int w);

#endif