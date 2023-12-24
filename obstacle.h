#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "graph.h"
#include "snake.h"  

extern int back_color;


typedef struct {
    int x;
    int y;
} Rock;


void Rock_Random(Rock Rocks[], int *nbrock);
void MoveRocks(Rock Rocks[], int nbrock);
int Snake_Obstacle_Collision(SnakeCase snake[], int length, Rock Rocks[], int nbrock);

#endif
