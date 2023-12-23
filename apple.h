#ifndef APPLE_H
#define APPLE_H
#include "snake.h"

typedef struct {
    int x;
    int y;
} Apple;

extern int score;

void Apples_Random(Apple Apples[], int *apples_number);
int Apple_Collision(int snake_x, int snake_y, int apple_x, int apple_y);
int Apple_Eating(SnakeCase snake[], Apple Apples[], int *apples_number, int *SnakeLength);
int Apples_Redraw(Apple Apples[], int apples_number);

#endif 