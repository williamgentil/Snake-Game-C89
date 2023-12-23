#ifndef SNAKE_H
#define SNAKE_H


typedef struct {
    int x;
    int y;
} SnakeCase;

void Init_Snake(SnakeCase snake[], int SnakeLength); 
void EraseSnake(SnakeCase snake[], int SnakeLength);
void MoveSnake(SnakeCase snake[], int direction, int SnakeLength);
int Snake_Self_Collision(SnakeCase snake[], int SnakeLength);
int Snake_OutOfBounds(int snake_x, int snake_y);
int Snake_Collision(int snake_x, int snake_y, int body_x, int body_y);

#endif 
