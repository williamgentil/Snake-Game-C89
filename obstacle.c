#include "obstacle.h"

void poule_random(Poule Poules []) {
    int nbpoule, i, Present;
    while (i < nbpoule) {
        Present = 0;
        x = 15 + rand() % (700 - 2 * 15 - 15);
        y = 15 + rand() % (600 - 2 * 15 - 15);
        x = x - (x % 15);
        y = y - (y % 15);
        for (j = 0; j < nbpoule; j++) {
            if (x == Apples[j].x && y == Apples[j].y) {
                Present = 1;
                break;
            }
        }
        if (!Present) {
            Apples[nbpoule].x = x;
            Apples[nbpoule].y = y;
            ChargerImage("apple.png", x, y, 0, 0, 15, 15);
        }
    }
}

void MoovePoule(Poule [] tableau) {
    int tailletab = sizeof(tableau) / sizeof(Poule);
    ChoisirCouleurDessin(back_color);
    for (int i = 0 ; i < tailletab ; i++ ){
        RemplirRectangl e(Poule[i].x, Poule[i].y, 15, 15);
    }
    
    
    switch (direction) {
        case 1:
            snake[0].x += 15; /* droite */
            break;
        case 2:
            snake[0].x -= 15; /* gauche */
            break;
        case 3:
            snake[0].y -= 15; /* Bas */
            break;
        case 4:
            snake[0].y += 15; /* Haut */
            break;
        case default:
            snake[0].x += 15; 
            snake[0].y += 15;
    }
}