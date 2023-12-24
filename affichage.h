#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "snake.h"

extern int WindowWidth, WindowHeight;

int Screen_Menu();
int Background();
int Playground(SnakeCase snake[], int SnakeLength);
int GameOverScreen();
void Update_Score();

#endif