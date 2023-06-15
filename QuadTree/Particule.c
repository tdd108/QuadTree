#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Particule.h"

Particule cree_particule(int x, int y) {
    Particule particule;
    particule.x = x;
    particule.y = y;
    return particule;
}

void generer_particule(Particule *tab_particule, int nb_particule, int w) {
    int x, y;
    for (int i = 0; i < nb_particule; i++) {
        x = rand() % w;
        y = rand() % w;
        tab_particule[i] = cree_particule(x, y);
    }
}

void generer_direction(int tab_direction[], int nb_particule) {
    int dir[16] = {0, 30, 45, 60, 90, 120, 135, 150, 180, 210, 225, 240, 270, 300, 315, 330}; 
    
    for (int i = 0; i < nb_particule; i++)
        tab_direction[i] = dir[rand() % 15];
}

void deplacer_particule(Particule *tab_particule, int tab_direction[], int nb_particule, int frame, int w) {
    int x_inc, y_inc;

    for (int i = 0; i < nb_particule; i++) {
        x_inc = 0;
        y_inc = 0;
        switch (tab_direction[i]) {
            case 0:
                x_inc = 1;
                break;

            case 30:
                if (frame == 2)
                    y_inc = -1;
                else 
                    x_inc = 1;
                break;

            case 45:
                x_inc = 1;
                y_inc = -1;
                break;

            case 60:
                if (frame == 2)
                    x_inc = 1;
                else
                    y_inc = -1;
                break;

            case 90:
                y_inc = -1;
                break;

            case 120:
                if (frame == 2)
                    x_inc = -1;
                else 
                    y_inc = -1;
                break;

            case 135:
                x_inc = -1;
                y_inc = -1;
                break;

            case 150:
                if (frame == 2)
                    y_inc = -1;
                else 
                    x_inc = -1;
                break;

            case 180:
                x_inc = -1;
                break;

            case 210:
                if (frame == 2)
                    y_inc = 1;
                else 
                    x_inc = -1;
                break;

            case 225:
                x_inc = -1;
                y_inc = 1;
                break;

            case 240:
                if (frame == 2)
                    x_inc = -1;
                else
                    y_inc = 1;
                break;

            case 270:
                y_inc = 1;
                break;

            case 300:
                if (frame == 2)
                    x_inc = 1;
                else 
                    y_inc = 1;
                break;

            case 315:
                x_inc = 1;
                y_inc = 1;
                break;

            case 330:
                if (frame == 2)
                    y_inc = 1;
                else 
                    x_inc = 1;
                break;

            default:
                break;
        }
        
        if (0 <= tab_particule[i].x && tab_particule[i].x <= w)
            tab_particule[i].x += x_inc;
        else {
            if (tab_particule[i].x < 0)
                tab_particule[i].x = 0;
            else 
                tab_particule[i].x = w;

            if (tab_direction[i] <= 180)
                tab_direction[i] = 180 - tab_direction[i];
            else
                tab_direction[i] = 180 + 360 - tab_direction[i];
        }
        
        if (0 <= tab_particule[i].y && tab_particule[i].y <= w)
            tab_particule[i].y += y_inc;
        else {
            if (tab_particule[i].y < 0)
                tab_particule[i].y = 0;
            else 
                tab_particule[i].y = w;

            tab_direction[i] = 360 - tab_direction[i];
        }
    }
}