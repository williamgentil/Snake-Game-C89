#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

#include "snake.h"
#include "apple.h"
#include "obstacle.h"
#include "graphics.h"
#include "utils.h"

#define CYCLE 100000L
#define PAUSE 100000L



int WindowWidth = 930;
int WindowHeight = 750;
int score = 0;
unsigned long int minutes = 0;
unsigned long seconds = 0;
unsigned long debutJeu;
unsigned long suivant;


int main() {
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
    debutJeu = Microsecondes();
    suivant = Microsecondes() + CYCLE;
    

    Screen_Menu();
    srand(time(NULL));
    Background();
    Init_Snake(snake, SnakeLength);
    Playground(snake, SnakeLength);

    while (go_on) {
        char temps_str[15];
        ChoisirCouleurDessin(back_color); /* permet de corriger partiellement le bug du pixel en x=0, y=0 */
        RemplirRectangle(0, 0, 15, 15);
        EraseSnake(snake, SnakeLength);
        Apples_Random(Apples, &apples_number);
        Update_Score();
            
        
        if (Apple_Eating(snake, Apples, &apples_number, &SnakeLength)) {
            SnakeLength += 2;
            Playground(snake, SnakeLength);
            ChoisirCouleurDessin(back_color);
            RemplirRectangle(825, 625, 100, 25);
            Apples_Redraw(Apples, apples_number);
        }

        MoveSnake(snake, direction, SnakeLength);
        last_direction = direction;
        if (Snake_Self_Collision(snake, SnakeLength)) {
            go_on = 0; 
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
                    ChargerImage("pause-menu.png", 0, 0, 0, 0, WindowWidth, WindowHeight);
                    while (Touche() != XK_space) {
                        go_on = 0;
                        if (ToucheEnAttente() == 1) {
                            switch (Touche()) {
                                case XK_Down:
                                    if (Pause_Menu_Position == 0) { /* resume */
                                        ChargerImage("green-arrow.png", 200, 300, 0, 0, 125, 70); 
                                        Pause_Menu_Position = Pause_Menu_Position+1;
                                        if (Touche() == XK_Return)
                                        {
                                            Background();
                                            Init_Snake(snake, SnakeLength);
                                            Playground(snake, SnakeLength);
                                            Apples[5];
                                            go_on = 1;
                                        }
                                    
                                        }
                                    else if (Pause_Menu_Position == 1) { /* bindings */
                                        Pause_Menu_Position = Pause_Menu_Position+1; 
                                        if (Touche() == XK_Return) {
                                            ChargerImageFond("keybinds.png");
                                        }
                                    }
                                    else if (Pause_Menu_Position == 2) { /*leave */
                                        Pause_Menu_Position = Pause_Menu_Position+1;
                                        if (Touche() == XK_Return) 
                                        {
                                            return 0;
                                        }
                                    
                                }
                                break;

                                case XK_Up:
                                    if (Pause_Menu_Position == 3) { /* bindings */
                                        Pause_Menu_Position = Pause_Menu_Position-1;
                                        if (Touche() == XK_Return) {
                                            ChargerImageFond("keybinds.png");
                                        }
                                    }
                                    else if (Pause_Menu_Position == 2) { /* resume */
                                        Pause_Menu_Position = Pause_Menu_Position-1;
                                        if (Touche() == XK_Return)
                                        {   
                                            Background();
                                            Init_Snake(snake, SnakeLength);
                                            Playground(snake, SnakeLength);
                                            Apples[5];
                                            go_on = 1;
                                        }
                                    }
                                    break;



                                case XK_space:
                                    Background();
                                    Init_Snake(snake, SnakeLength);
                                    Playground(snake, SnakeLength);
                                    Apples[5];
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
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}