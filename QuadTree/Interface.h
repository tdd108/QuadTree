#ifndef INTERFACE_H
#define INTERFACE_H

#include "QuadTree.h"

void placer_particule(int *nb_particule, Particule *tab_particule);

void afficher_particule(Particule *tab_particule, int nb_particule);

void afficher_particule_v2(Particule *tab_particule, int nb_particule);

void afficher_quadtree(QuadTree arbre, int index);

void afficher_plein_cell(Noeud noeud);

void menu(int *mode);

#endif