#ifndef APPLE_H
#define APPLE_H

typedef struct {
    int x;
    int y;
} Apple;

void Apples_Random(Apple Apples[], int *apples_number);
int Apple_Eating(SnakeCase snake[], Apple Apples[], int *apples_number, int *SnakeLength);
int Apple_Collision(int snake_x, int snake_y, int apple_x, int apple_y);
void Apples_Redraw(Apple Apples[], int apples_number);

#endif
