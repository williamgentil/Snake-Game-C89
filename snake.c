#include "snake.h"
#include <graph.h>


/* Initialise le serpent avec une longueur initiale */
void Init_Snake(SnakeCase snake[], int SnakeLength) {
    int i;
    int x_middle = 60 / 2;
    int y_middle = 40 / 2;
    for (i = 0; i < SnakeLength; i++) {
        snake[i].x = (x_middle - SnakeLength / 2 + i) * 15;
        snake[i].y = y_middle * 15;
    }   
}


/* Efface le serpent du terrain */

void EraseSnake(SnakeCase snake[], int SnakeLength) {
    int i;
    int black = CouleurParComposante(0, 0, 0); 
    ChoisirCouleurDessin(black);
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 15, 15);
    }
}


/* Déplace le serpent en fonction de la direction donnée */

void MoveSnake(SnakeCase snake[], int direction, int SnakeLength) {
    int i;
    int couleur_serpent = CouleurParComposante(117, 253, 62);
    EraseSnake(snake, SnakeLength);
    for (i = SnakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
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
    }
    ChoisirCouleurDessin(couleur_serpent);
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 15, 15);
    }
}


/* Vérifie la collision du serpent avec lui-même */
int Snake_Self_Collision(SnakeCase snake[], int SnakeLength) {
    int i;
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    for (i = 1; i < SnakeLength; i++) {
        if (Snake_Collision(head_x, head_y, snake[i].x, snake[i].y)) {
            return 1; 
        }
    }
    return 0;
}
/* Vérifie si le serpent est en dehors des limites du terrain */


int Snake_OutOfBounds(int snake_x, int snake_y) {
    return snake_x < 15 || snake_x >= 900 || snake_y < 15 || snake_y >= 600;
}

/* Vérifie la collision entre la tête du serpent et une partie de son corps */


int Snake_Collision(int snake_x, int snake_y, int body_x, int body_y) {
    return snake_x == body_x && snake_y == body_y; 
}