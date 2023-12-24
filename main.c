#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

#include "affichage.h"
#include "apple.h"
#include "game.h"
#include "snake.h"
#include "obstacle.h"

#define delta 1000000L
#define CYCLE 100000L
#define MAX_LENGTH 500
#define PAUSE 100000L

int main() {
    Rock obstacles[50]; 
    int nb_obstacles = 50;
    int direction = 2, go_on = 1;
    int Pause_Menu_Position = 0;
    int last_direction = 0;
    int SnakeLength = 10;
    int back_color = CouleurParComposante(140, 25, 0);
    SnakeCase *snake = (SnakeCase *)malloc(MAX_LENGTH * sizeof(SnakeCase));
    Apple Apples[5];
    int apples_number = 0;
    int delay = 80000;
    int delaymin = 20000;
    unsigned long minutes = 0;
    unsigned long seconds = 0;

    Screen_Menu();
    srand(time(NULL));
    Background();
    Init_Snake(snake, SnakeLength);
    Playground(snake, SnakeLength);
    Apples_Redraw(Apples, apples_number);
    Rock_Random(obstacles, &nb_obstacles);

  
    /* Boucle principale du jeu */
    while (go_on) {
        char temps_str[100];
        char score_str[15];
        ChoisirCouleurDessin(back_color); 
        RemplirRectangle(0, 0, 15, 15);
        EraseSnake(snake, SnakeLength);
        Apples_Random(Apples, &apples_number);
        Update_Score();
        Playground(snake, SnakeLength);
        Apples_Redraw(Apples, apples_number);
        MoveRocks(obstacles, nb_obstacles);
        Keys();
        
        if (Apple_Eating(snake, Apples, &apples_number, &SnakeLength)) {
            SnakeLength += 2;
            Playground(snake, SnakeLength);
            ChoisirCouleurDessin(back_color);
            RemplirRectangle(WindowWidth - 120, WindowHeight - 130, 150, 50);
            Apples_Redraw(Apples, apples_number);
        }
        MoveSnake(snake, direction, SnakeLength);
        last_direction = direction;


        if (snake[0].x < 15 || snake[0].x >= 900 || snake[0].y < 15 || snake[0].y >= 600) {
            go_on = 0;
        }

         if (Snake_Self_Collision(snake, SnakeLength) || Snake_OutOfBounds(snake[0].x, snake[0].y)) {
            go_on = 0;
            GameOverScreen();
            switch (Touche()) {
            case XK_Return : 
                FermerGraphique();
                Screen_Menu();    
            break;
        
            case XK_Escape : 
                return 0;
            break;
    }

        }

        
       if (Snake_Obstacle_Collision(snake, SnakeLength, obstacles, nb_obstacles)) {
 
            go_on = 0;
            GameOverScreen();
            switch (Touche()) {
            case XK_Return : 
                FermerGraphique();
                Screen_Menu();    
            break;
        
            case XK_Escape : 
                return;
            break;
    }
        }

        if (Microsecondes() > suivant) {
            suivant = Microsecondes() + CYCLE;
            Timer(PAUSE);
            ChoisirCouleurDessin(back_color);
            RemplirRectangle(50, 625, 50, 25);
            seconds = SecondesDepuisDebut();
            sprintf(temps_str, "%02lu:%02lu", minutes, seconds);
            ChoisirCouleurDessin(CouleurParNom("black"));
            EcrireTexte(25, WindowHeight - 100, temps_str, 2);
        }
    /*  Gestion des événements (touches, pause, etc.) */
        if (ToucheEnAttente() == 1) {
            switch (Touche()) {
                case XK_Right:
                    direction = 1;
                    if (last_direction == 2 && direction == 1) {
                        direction = last_direction;
                    }
                    break;
                case XK_Left:
                    direction = 2;
                    if (last_direction == 1 && direction == 2) {
                        direction = last_direction;
                    }
                    break;
                case XK_Up:
                    direction = 3;
                    if (last_direction == 4 && direction == 3) {
                        direction = last_direction;
                    }
                    break;
                case XK_Down:
                    direction = 4;
                    if (last_direction == 3 && direction == 4) {
                        direction = last_direction;
                    }
                    break;
                case XK_Escape:
                    return 0;
                    break;
                case XK_space:
                    ChargerImage("pause-menu.png", WindowWidth/2 - 150, WindowHeight/2 -250, 0, 0, 930, 750);
                    sprintf(temps_str, "%02lu s", seconds);
                    ChoisirCouleurDessin(CouleurParComposante(99, 99, 99));
                    EcrireTexte(WindowWidth/2, WindowHeight/2 - 100, temps_str, 1);
                    sprintf(score_str, "%06d", score);
                    EcrireTexte(WindowWidth/2 - 80, WindowHeight/2 - 100, score_str, 1);
                    while (Touche() != XK_space) {
                        go_on = 0;
                        if (ToucheEnAttente() == 1) {
                            switch (Touche()) {
                                case XK_space:
                                    go_on = 1;
                                    break;
                                case XK_Escape:
                                    free(snake);
                                    return 0;
                                    break;
                        }
                    }
                }
                    break;
                
                    
            }
        }
        
    }
 
    free(snake);
    if(Touche() == XK_Escape) {
    FermerGraphique();
    return EXIT_SUCCESS;
    }
}