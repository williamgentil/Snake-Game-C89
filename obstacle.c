#include "obstacle.h"
#include <graph.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int back_color;
/* Génère des rochers aléatoires sur le terrain */
void Rock_Random(Rock Rocks[], int *nbrock) {
    int i = 0;
    int x, y, j, Present;

    while (i < *nbrock) {
        Present = 0;
        x = 15 + rand() % (900 - 2 * 15 - 15);
        y = 15 + rand() % (600 - 2 * 15 - 15);
        x = x - (x % 15);
        y = y - (y % 15);

        j = 0;
        while (j < i) {
            if (x == Rocks[j].x && y == Rocks[j].y) {
                Present = 1;
                break;
            }
            j++;
        }

        if (!Present) {
            Rocks[i].x = x;
            Rocks[i].y = y;
            ChargerImage("rock.png", x, y, 0, 0, 15, 15);
            i++;
        }
    }
}

void MoveRocks(Rock Rocks[], int nbrock) {
    int i;
    for (i = 0; i < nbrock; i++) {
        ChargerImage("rock.png",Rocks[i].x, Rocks[i].y, 0, 0, 15, 15);
       
    }
}
/*  Vérifie la collision entre le serpent et un rocher */
int Snake_Obstacle_Collision(SnakeCase snake[], int length, Rock Rocks[], int nbrock) {
    int i;
    for (i = 0; i < nbrock; i++) {
        if (snake[0].x == Rocks[i].x && snake[0].y == Rocks[i].y) {
            return 1; 
        }
        
    }
    return EXIT_SUCCESS;
}

