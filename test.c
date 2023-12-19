#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>


#define delta 1000000L
#define CYCLE 100000L
#define MAX_LENGTH 200
#define PAUSE 100000L

int windowWidth = 1100;
int windowHeight = 600;
int score = 0;
unsigned long temps = 0;
unsigned long debutJeu;
unsigned long suivant;

typedef struct {
    int x;
    int y;
} SnakeCase;

typedef struct {
    int x;
    int y;
} Apple;

void Temps(unsigned long us) {
    unsigned long attente = Microsecondes() + us;
    while (Microsecondes() < attente) {}
}
unsigned long MicrosecondesDepuisDebut() {
    return Microsecondes() - debutJeu;
}

unsigned long SecondesDepuisDebut() {
    return MicrosecondesDepuisDebut() / 1000000L;
}

void Init_Snake(SnakeCase snake[], int SnakeLength) {
    int i;
    int x_middle = 60 / 2;
    int y_middle = 40 / 2;
    for (i = 0; i < SnakeLength; i++) {
        snake[i].x = (x_middle - SnakeLength / 2 + i) * 20;
        snake[i].y = y_middle * 20;
    }   
}

int Screen_Menu() {

    InitialiserGraphique();
    CreerFenetre(10, 10, 1100, 600);
    ChargerImageFond("./snake-screenmenu.png");
    ChargerImage("./green-arrow.png", 10, 420, 0, 0, 125, 70); /* not working */


    while (1) {
        if (SourisCliquee()) {
            int x = _X;
            int y = _Y;
            if ((x >= 100 && x <= 350) && (y >= 370 && y <= 470)) {
                ChoisirEcran(0);
                break;
            } else if ((x >= 710 && x <= 1050) && (y >= 370 && y <= 470)) {
                FermerGraphique();
                return EXIT_SUCCESS;
            }
        }
    }
}

int Background() {
    int b_color = CouleurParComposante(140, 25, 0);
    ChoisirCouleurDessin(b_color);
    RemplirRectangle(0, 0, 1100, 600);
}

int Playground(SnakeCase snake[], int SnakeLength) {
    int black = CouleurParComposante(0, 0, 0);
    int i;
    int couleur_serpent = CouleurParComposante(117, 253, 62);
    ChoisirCouleurDessin(black);
    RemplirRectangle(20, 20, 700, 600);

    for (i = 0; i < SnakeLength; i++) {
        ChargerImage("./snake-head.png", snake[i].x, snake[i].y, 0, 0, 20, 20);
    }
}

void EraseSnake(SnakeCase snake[], int SnakeLength) {
    int i;
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 20, 20);
    }
}


void MoveSnake(SnakeCase snake[], int direction, int SnakeLength) {
    int i;

    EraseSnake(snake, SnakeLength);
    for (i = SnakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case 1:
            snake[0].x += 20; /* droite */
            break;
        case 2:
            snake[0].x -= 20; /* gauche */
            break;
        case 3:
            snake[0].y -= 20; /* Bas */
            break;
        case 4:
            snake[0].y += 20; /* Haut */
            break;
    }

    for (i = 0; i < SnakeLength; i++) {
        ChargerImage("./snake-head.png", snake[i].x, snake[i].y, 0, 0, 20, 20);
    }
}

int Snake_Self_Collision(SnakeCase snake[], int SnakeLength) {
    int i;
    int head_x = snake[0].x;
    int head_y = snake[0].y;


    for (i = 1; i < SnakeLength; i++) {
        if (Snake_Collision(head_x, head_y, snake[i].x, snake[i].y)) {
            return 1; 
        }
    }

    return 0;
}

void Apples_Random(Apple Apples[], int *apples_number) {

    int i, x, y, j;
    int Present = 0;

    while (*apples_number < 5) {
        Present = 0;
        x = 20 + rand() % (700 - 2 * 20 - 20);
        y = 20 + rand() % (600 - 2 * 20 - 20);
        x = x - (x % 20);
        y = y - (y % 20);

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
            ChargerImage("./apple.png", x, y, 0, 0, 20, 20);
        }
    }
}

int Apple_Collision(int snake_x, int snake_y, int apple_x, int apple_y) {

    return snake_x == apple_x && snake_y == apple_y;
}


int Wall_Collision(int snake_x, int snake_y, int wall_x, int wall_y) { /* à init */

    return snake_x == wall_x && snake_y == wall_y;
}

int Snake_Collision(int snake_x, int snake_y, int body_x, int body_y) { /* à init */

    return snake_x == body_x && snake_y == body_y; 
}

 int Apple_Eating(SnakeCase snake[], Apple Apples[], int *apples_number, int *SnakeLength) {
    int i, j;
    int head_x = snake[0].x;
    int head_y = snake[0].y;

    for (i = 0; i < *apples_number; i++) {
        if (Apple_Collision(head_x, head_y, Apples[i].x, Apples[i].y)) {
            for (j = *SnakeLength - 1; j > 0; j--) {
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

int Apples_Redraw(Apple Apples[], int apples_number) {
    int i;

    for (i = 0; i < apples_number; i++) {
        ChargerImage("./apple.png", Apples[i].x, Apples[i].y, 0, 0, 20, 20);
    }
}

void Update_Score() {
    char score_str[15];
    sprintf(score_str, "Score: %d", score);
    EcrireTexte(windowWidth- 150, windowHeight - 50, score_str, 2);
}

int main() {
    int direction = 2, go_on = 1;
    int Pause_Menu_Position = 0;
    int last_direction = 0;
    int SnakeLength = 10;
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
        EraseSnake(snake, SnakeLength);
        Apples_Random(Apples, &apples_number);
        Update_Score();
            
        
        if (Apple_Eating(snake, Apples, &apples_number, &SnakeLength)) {
            SnakeLength += 2;
            Background();
            Playground(snake, SnakeLength);
            Apples_Redraw(Apples, apples_number);
        }

        MoveSnake(snake, direction, SnakeLength);
        last_direction = direction;
        if (Snake_Self_Collision(snake, SnakeLength)) {
            printf("TEST!\n");
            go_on = 0; 
        }
        if (Microsecondes() > suivant) {
            suivant = Microsecondes() + CYCLE;
            Temps(PAUSE);
            temps = SecondesDepuisDebut();
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(20, 20, 200, 30);
            sprintf(temps_str, "Temps: %lu s", temps);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(windowWidth - 150, windowHeight - 30, temps_str, 2);

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
                case XK_space:
                    ChargerImage("./pause-menu.png", 0, 0, 0, 0, 1100, 600);
                    if (ToucheEnAttente() == 1) {
                        switch (Touche()) {
                            case XK_Down:
                                if (Pause_Menu_Position == 0) {
                                    ChargerImage("./green-arrow.png", 200, 300, 0, 0, 125, 70);/* mettre la position de la souris au niveau de resume */
                                    Pause_Menu_Position = Pause_Menu_Position+1;
                                    if (Touche() == XK_Return)
                                    {
                                        ChoisirEcran(0);
                                    }
                                    
                                    }
                                else if (Pause_Menu_Position == 1) {
                                    SourisPosition(); /* mettre la position de la souris au niveau de bindings */
                                    Pause_Menu_Position = Pause_Menu_Position+1;
                                    if (Touche() == XK_Return) {
                                        ChargerImageFond("./keybinds.png");
                                    }
                                }
                                else if (Pause_Menu_Position == 2) {
                                    SourisPosition(); /* mettre la position de la souris au niveau de leave */
                                    Pause_Menu_Position = Pause_Menu_Position+1;
                                    if (Touche() == XK_Return) 
                                    {
                                        return 0;
                                    }
                                    
                                }
                                break;

                            case XK_Up:
                                if (Pause_Menu_Position == 3) {
                                    SourisPosition(); /* mettre la position de la souris au niveau de bindings */
                                    Pause_Menu_Position = Pause_Menu_Position-1;
                                    if (Touche() == XK_Return) {
                                        ChargerImageFond("./keybinds.png");
                                    }
                                }
                                else if (Pause_Menu_Position == 2) {
                                    SourisPosition(); /* mettre la position de la souris au niveau de resume */
                                    Pause_Menu_Position = Pause_Menu_Position-1;
                                    if (Touche() == XK_Return)
                                    {
                                        ChoisirEcran(0);
                                    }
                                }
                                break;



                            case XK_space:
                                ChoisirEcran(0); /* régler le problème pour avoir la fenêtre du jeu */
                                break;

                            case XK_Escape:
                                return 0;
                                break;
                        }
                    }
                    break;
                case XK_Escape:
                    return 0;
                    break;

                    
            }
        }

        
    }
 

    free(snake);
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}