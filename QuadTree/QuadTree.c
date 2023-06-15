#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "QuadTree.h"

void initialiser_noeud(Noeud *noeud, int index, Noeud noeud_parent, int indice_racine, int Kp) {
    Point centre;

    switch (index % 4) {
        case NORD_OUEST:
            centre.x = noeud_parent.centre.x - noeud_parent.demi_dimension / 2;
            centre.y = noeud_parent.centre.y - noeud_parent.demi_dimension / 2;
            break;
        case NORD_EST:
            centre.x = noeud_parent.centre.x + noeud_parent.demi_dimension / 2;
            centre.y = noeud_parent.centre.y - noeud_parent.demi_dimension / 2;
            break;
        case SUD_OUEST:
            centre.x = noeud_parent.centre.x - noeud_parent.demi_dimension / 2;
            centre.y = noeud_parent.centre.y + noeud_parent.demi_dimension / 2;
            break;
        case SUD_EST:
            centre.x = noeud_parent.centre.x + noeud_parent.demi_dimension / 2;
            centre.y = noeud_parent.centre.y + noeud_parent.demi_dimension / 2;
            break;
        default:
            break;
    }

    for (int i = 0; i < Kp; i++)
        noeud->plist[i] = -1;

    noeud->nbp = 0;
    noeud->centre = centre;
    noeud->demi_dimension = noeud_parent.demi_dimension / 2;
    noeud->est_feuille = 0;

    if (4 * index + 4 <= indice_racine - 1) {
        noeud->NordOuest = 4 * index + 1;
        noeud->NordEst = 4 * index + 2;
        noeud->SudOuest = 4 * index + 3;
        noeud->SudEst = 4 * index + 4;
    }
    else {
        // -1 est vide
        noeud->NordOuest = -1;
        noeud->NordEst = -1;
        noeud->SudOuest = -1;
        noeud->SudEst = -1;
    }
}

QuadTree initialiser_quadtree(int w, int Wmin, int Kp) {
    QuadTree arbre = NULL;

    int hauteur = log2(w) - log2(Wmin);
    int nb_noeud = (pow(4, hauteur + 1) - 1) / 3;

    arbre = (Noeud *)malloc(nb_noeud * sizeof(Noeud));

    if (arbre == NULL)
        return NULL;

    //initialiser racine
    arbre[0].nbp = 0;
    arbre[0].centre.x = w / 2;
    arbre[0].centre.y = w / 2;
    arbre[0].demi_dimension = w / 2;
    arbre[0].est_feuille = 1;

    arbre[0].NordOuest = 1;
    arbre[0].NordEst = 2;
    arbre[0].SudOuest = 3;
    arbre[0].SudEst = 4;

    for (int i = 0; i < Kp; i++)
        arbre[0].plist[i] = -1;

    for (int i = 1; i < nb_noeud; i++)
        initialiser_noeud(&arbre[i], i, arbre[(i - 1) / 4], nb_noeud, Kp);

    return arbre;
}

bool contenir_point(Noeud noeud, Particule particule) {
    if (noeud.centre.x - noeud.demi_dimension <= particule.x
        && particule.x < noeud.centre.x + noeud.demi_dimension
        && noeud.centre.y - noeud.demi_dimension <= particule.y
        && particule.y < noeud.centre.y + noeud.demi_dimension)
        return true;
    return false;
}

void redistribuer(QuadTree arbre, int indice_noeud, Particule *tab_particule, int Kp, int Wmin) {
    if (arbre == NULL)
        return;
    
    int indice;
    int nbp = arbre[indice_noeud].nbp;

    for (int i = 0; i < Kp; i++) {
        indice = arbre[indice_noeud].plist[i];
        arbre[indice_noeud].plist[i] = -1; //vider la liste
        if (indice == -1)
            continue;
        inserer(arbre, arbre[indice_noeud].NordOuest, indice, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].NordEst, indice, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].SudOuest, indice, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].SudEst, indice, tab_particule, Kp, Wmin);
    }
    arbre[indice_noeud].nbp = nbp;
}

int inserer(QuadTree arbre, int indice_noeud, int indice_parti, Particule *tab_particule, int Kp, int Wmin) {
    if (arbre == NULL)
        return -1;
    
    if (!contenir_point(arbre[indice_noeud], tab_particule[indice_parti])) {
        return -1;
    }
    
    if (arbre[indice_noeud].nbp < Kp || 2 * arbre->demi_dimension == Wmin) {
        if (arbre[indice_noeud].est_feuille == 0)
            arbre[indice_noeud].est_feuille = 1;
        arbre[indice_noeud].plist[arbre[indice_noeud].nbp] = indice_parti;
        arbre[indice_noeud].nbp++;
        return indice_noeud;
    }
    else if (arbre[indice_noeud].NordOuest != -1){
        if (arbre[indice_noeud].est_feuille == 1) {
            arbre[indice_noeud].est_feuille = 0;
            redistribuer(arbre, indice_noeud, tab_particule, Kp, Wmin);
        }

        inserer(arbre, arbre[indice_noeud].NordOuest, indice_parti, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].NordEst, indice_parti, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].SudOuest, indice_parti, tab_particule, Kp, Wmin);
        inserer(arbre, arbre[indice_noeud].SudEst, indice_parti, tab_particule, Kp, Wmin);

        arbre[indice_noeud].nbp++;
        return indice_noeud;
    }
    return -1;
}

void reinitialiser_quadtree(QuadTree arbre, int indice_racine) {
    if (arbre[indice_racine].nbp != 0) {
        if (arbre[indice_racine].est_feuille == 1) {
            arbre[indice_racine].est_feuille = 0;
            for (int j = 0; j < arbre[indice_racine].nbp; j++)
                arbre[indice_racine].plist[j] = -1;
        }
        arbre[indice_racine].nbp = 0;

        if (arbre[indice_racine].NordOuest != -1) {
            reinitialiser_quadtree(arbre, arbre[indice_racine].NordOuest);
            reinitialiser_quadtree(arbre, arbre[indice_racine].NordEst);
            reinitialiser_quadtree(arbre, arbre[indice_racine].SudOuest);
            reinitialiser_quadtree(arbre, arbre[indice_racine].SudEst);
        }
    }
}

void liberer_quadtree(QuadTree arbre, int nb_noeud) {
    for (int i = 0; i < nb_noeud; i++)
        free(&arbre[i]);
    free(arbre);
}