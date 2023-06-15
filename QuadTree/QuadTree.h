#ifndef QUADTREE_H
#define QUADTREE_H

#define NB_MAX_P 500

#include <stdbool.h>

#include "Particule.h"

typedef enum {
    NORD_OUEST = 1,
    NORD_EST = 2,
    SUD_OUEST = 3,
    SUD_EST = 0
} Direction;

typedef struct noeud {
    int nbp;

    Point centre;
    int demi_dimension;

    int est_feuille;

    int plist[NB_MAX_P];

    int NordOuest;
    int NordEst;
    int SudOuest;
    int SudEst;
} Noeud, *QuadTree;

void initialiser_noeud(Noeud *noeud, int index, Noeud noeud_parent, int nb_noeud, int Kp);

QuadTree initialiser_quadtree(int w, int wmin, int Kp);

bool contenir_point(Noeud noeud, Particule particule);

void redistribuer(QuadTree arbre, int indice_noeud, Particule *tab_particule, int Kp, int Wmin);

int inserer(QuadTree arbre, int indice_noeud, int indice_parti, Particule *tab_particule, int Kp, int Wmin);

void reinitialiser_quadtree(QuadTree arbre, int indice_racine);

void liberer_quadtree(QuadTree arbre, int nb_noeud);

#endif