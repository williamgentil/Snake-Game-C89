#ifndef OBSTACLE_H
#define OBSTACLE_H

#define MAX_OBSTACLES 10
typedef struct {
    int x;
    int y;
} Obstacle;

void Init_Obstacles();
void Display_Obstacles();
int Obstacle_Collision(int snake_x, int snake_y);

#endif
