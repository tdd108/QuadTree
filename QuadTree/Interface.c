#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "Interface.h"

void placer_particule(int *nb_particule, Particule *tab_particule) {
	int x, y;
	
	MLV_wait_mouse(&x, &y);

	for (int i = 0; i < *nb_particule; i++) {
		if (x - 5 <= tab_particule[i].x && tab_particule[i].x <= x + 5
			&& y - 5 <= tab_particule[i].y && tab_particule[i].y < y + 5) {
				while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
					MLV_get_mouse_position(&x, &y);
					tab_particule[i].x = x;
					tab_particule[i].y = y;
					MLV_clear_window(MLV_COLOR_WHITE);
					afficher_particule_v2(tab_particule, *nb_particule);
					MLV_update_window();
				}
			return;
		}
	}
	tab_particule[*nb_particule] = cree_particule(x, y);
	*nb_particule += 1;
}

void afficher_particule(Particule *tab_particule, int nb_particule) {
	int x, y;
	for (int i = 0; i < nb_particule; i++) {
		x = tab_particule[i].x;
		y = tab_particule[i].y;
		MLV_draw_filled_rectangle(x - 1 , y - 1, 3, 3, MLV_COLOR_RED);
	}
}

void afficher_particule_v2(Particule *tab_particule, int nb_particule) {
	int x, y;
	for (int i = 0; i < nb_particule; i++) {
		x = tab_particule[i].x;
		y = tab_particule[i].y;
		MLV_draw_filled_circle(x, y, 5, MLV_COLOR_RED);
	}
}

void afficher_quadtree(QuadTree arbre, int index) {
	int x, y, w, h;

	x = arbre[index].centre.x - arbre[index].demi_dimension;
	y = arbre[index].centre.y - arbre[index].demi_dimension;
	w = 2 * arbre[index].demi_dimension;
	h = 2 * arbre[index].demi_dimension;
	
	if (arbre[index].est_feuille) {
		MLV_draw_filled_rectangle(x, y, w, h, MLV_COLOR_GRAY);
		MLV_draw_rectangle(x, y, w + 1, h + 1, MLV_COLOR_DIM_GRAY);
		return;
	}
	else if (arbre[index].NordOuest != -1) {
		afficher_quadtree(arbre, arbre[index].NordOuest);
		afficher_quadtree(arbre, arbre[index].NordEst);
		afficher_quadtree(arbre, arbre[index].SudOuest);
		afficher_quadtree(arbre, arbre[index].SudEst);
	}
}

void afficher_plein_cell(Noeud noeud) {
	MLV_draw_text(10, 120, "Cell Plein", MLV_COLOR_BLUE);
	MLV_update_window();
}

void menu(int *mode) {
	MLV_Keyboard_button touche;

	MLV_draw_text(0, 0, "Choisir mode", MLV_COLOR_BLACK);
    MLV_draw_text(0, 15, "1 : distribution aléatoire", MLV_COLOR_BLACK);
    MLV_draw_text(0, 30, "2 : distribution au clic-souris", MLV_COLOR_BLACK);
    MLV_update_window();
    while (*mode == 0) {
        MLV_wait_keyboard(&touche, NULL, NULL);
        if (touche == MLV_KEYBOARD_1)
            *mode = 1;
        else if (touche == MLV_KEYBOARD_2)
            *mode = 2;
    }
}