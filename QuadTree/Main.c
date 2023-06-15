#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "QuadTree.h"
#include "Particule.h"
#include "Interface.h"

#define Kp 1
#define W 512
#define Wmin 2
#define NB_PARTICULE 100
#define NB_MAX_PARTICULE 100

int main() {

    srand(time(NULL));
        
    int mode = 0;
    int nb_particule = 0;

    Particule *tab_particule = (Particule *)malloc(NB_MAX_PARTICULE * sizeof(Particule));
    QuadTree arbre = initialiser_quadtree(W, Wmin, Kp);

    MLV_create_window("Quad Tree", "quad", W, W);
    MLV_clear_window(MLV_COLOR_WHITE);

    menu(&mode);
    
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();

    if (mode == 1) {
        int frame = 0;
        nb_particule = NB_PARTICULE;
        int tab_direction[nb_particule];

        generer_particule(tab_particule, nb_particule, W);
        generer_direction(tab_direction, nb_particule);

        for (int i = 0; i < nb_particule; i++)
            inserer(arbre, 0, i, tab_particule, Kp, Wmin);

        while (1) {
            afficher_quadtree(arbre, 0);
            afficher_particule(tab_particule, nb_particule);
            MLV_update_window();
            deplacer_particule(tab_particule, tab_direction, nb_particule, frame, W);
            frame++;
            if (frame == 3)
                frame = 0;
            reinitialiser_quadtree(arbre, 0);
            for (int i = 0; i < nb_particule; i++)
                inserer(arbre, 0, i, tab_particule, Kp, Wmin);
            MLV_clear_window(MLV_COLOR_WHITE);
        } 
    } else {

        while (1) {
            afficher_quadtree(arbre, 0);
            afficher_particule_v2(tab_particule, nb_particule);
            MLV_update_window();
            placer_particule(&nb_particule, tab_particule);
            reinitialiser_quadtree(arbre, 0);
            for (int i = 0; i < nb_particule; i++)
                inserer(arbre, 0, i, tab_particule, Kp, Wmin);
                
            MLV_clear_window(MLV_COLOR_WHITE);
        }
    }

    free(arbre);
    free(tab_particule);

    MLV_wait_seconds( 10 );
    MLV_free_window();

    return 0;
}