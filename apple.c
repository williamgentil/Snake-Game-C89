#include "apple.h"
#include "snake.h"
#include <graph.h>
#include <time.h>
#include <stdlib.h>

int score;


/* Génère des pommes aléatoires sur le terrain */
void Apples_Random(Apple Apples[], int *apples_number) {
    int i, x, y, j;
    int Present = 0;
    while (*apples_number < 5) {
        Present = 0;
        x = 15 + rand() % (900 - 2 * 15 - 15);
        y = 15 + rand() % (600 - 2 * 15 - 15);
        x = x - (x % 15);
        y = y - (y % 15);
        for (j = 0; j < *apples_number; j++) {
            if (x == Apples[j].x && y == Apples[j].y) {
                Present = 1;
                break;
            }
        }
        if (!Present) {
            Apples[*apples_number].x = x;
            Apples[*apples_number].y = y;
            (*apples_number)++;
            ChargerImage("apple.png", x, y, 0, 0, 15, 15);
        }
    }
}

/* Vérifie la collision entre la tête du serpent et une pomme */

int Apple_Collision(int snake_x, int snake_y, int apple_x, int apple_y) {
    return snake_x == apple_x && snake_y == apple_y;
}


/* Traite la collision entre le serpent et une pomme */

int Apple_Eating(SnakeCase snake[], Apple Apples[], int *apples_number, int *SnakeLength) {
    int i, j, back_color = CouleurParComposante(117, 253, 62);
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    for (i = 0; i < *apples_number; i++) {
        if (Apple_Collision(head_x, head_y, Apples[i].x, Apples[i].y)) {
            for (j = *SnakeLength - 1; j > 0; j--) {
                ChoisirCouleurDessin(back_color); /* permet de corriger partiellement le bug du pixel en x=0, y=0 */
                RemplirRectangle(0, 0, 15, 15);
                snake[j] = snake[j - 1];
            }
            snake[0].x = Apples[i].x;
            snake[0].y = Apples[i].y;
            for (j = i; j < *apples_number - 1; j++) {
                Apples[j].x = Apples[j + 1].x;
                Apples[j].y = Apples[j + 1].y;
            }
            (*apples_number)--;
            score += 5;  
            return 1;
        }
    }
    return 0;
} 

/* Réaffiche toutes les pommes sur le terrain */

int Apples_Redraw(Apple Apples[], int apples_number) {
    int i;
    for (i = 0; i < apples_number; i++) {
        ChargerImage("apple.png", Apples[i].x, Apples[i].y, 0, 0, 15, 15);
    }
}