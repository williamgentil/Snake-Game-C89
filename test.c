#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h> 

#define delta 1000000L
#define CYCLE 100000L
#define MAX_LENGTH 500
#define PAUSE 100000L

int WindowWidth = 930;
int WindowHeight = 750;
int score = 0;
unsigned long int minutes = 0;
unsigned long seconds = 0;
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

void Timer(unsigned long us) {
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
        snake[i].x = (x_middle - SnakeLength / 2 + i) * 15;
        snake[i].y = y_middle * 15;
    }   
}
int Screen_Menu() {
    InitialiserGraphique();
    CreerFenetre(10, 10, WindowWidth, WindowHeight);
    ChargerImageFond("snake-screenmenu.png");
    ChargerImage("green-arrow.png", 10, 420, 0, 0, 125, 70); /* not working */
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
    int back_color = CouleurParComposante(140, 25, 0);
    ChoisirCouleurDessin(back_color);
    RemplirRectangle(0, 0, WindowWidth, WindowHeight);
}
int Playground(SnakeCase snake[], int SnakeLength) {
    int black = CouleurParComposante(0, 0, 0);
    int i;
    int couleur_serpent = CouleurParComposante(117, 253, 62);
    ChoisirCouleurDessin(black);
    RemplirRectangle(15, 15, 900, 600);
    ChoisirCouleurDessin(couleur_serpent);
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 15, 15);
    }
}
void EraseSnake(SnakeCase snake[], int SnakeLength) {
    int i;
    int black = CouleurParComposante(0, 0, 0); 
    ChoisirCouleurDessin(black);
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 15, 15);
    }
}
void MoveSnake(SnakeCase snake[], int direction, int SnakeLength) {
    int i;
    int tempsecoule = 2 ;
    int couleur_serpent = CouleurParComposante(117, 253, 62);
    EraseSnake(snake, SnakeLength);
    for (i = SnakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    switch (direction) {
        case 1:
            snake[0].x += 15* tempsecoule; /* droite */
            break;
        case 2:
            snake[0].x -= 15 * tempsecoule; /* gauche */
            break;
        case 3:
            snake[0].y -= 15 * tempsecoule; /* Bas */
            break;
        case 4:
            snake[0].y += 15 * tempsecoule; /* Haut */
            break;
    }
    ChoisirCouleurDessin(couleur_serpent);
    for (i = 0; i < SnakeLength; i++) {
        RemplirRectangle(snake[i].x, snake[i].y, 15, 15);
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

int Snake_OutOfBounds(int snake_x, int snake_y) {
    return snake_x < 15 || snake_x >= 900 || snake_y < 15 || snake_y >= 600;
}

void Apples_Random(Apple Apples[], int *apples_number) {
    int i, x, y, j;
    int Present = 0;
    while (*apples_number < 5) {
        Present = 0;
        x = 15 + rand() % (700 - 2 * 15 - 15);
        y = 15 + rand() % (600 - 2 * 15 - 15);
        x = x - (x % 15);
        y = y - (y % 15);
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
            ChargerImage("apple.png", x, y, 0, 0, 15, 15);
        }
    }
}
int Apple_Collision(int snake_x, int snake_y, int apple_x, int apple_y) {
    return snake_x == apple_x && snake_y == apple_y;
}

int Snake_Collision(int snake_x, int snake_y, int body_x, int body_y) { /* à init */
    return snake_x == body_x && snake_y == body_y; 
}
 int Apple_Eating(SnakeCase snake[], Apple Apples[], int *apples_number, int *SnakeLength) {
    int i, j, back_color = CouleurParComposante(117, 253, 62);
    int head_x = snake[0].x;
    int head_y = snake[0].y;
    for (i = 0; i < *apples_number; i++) {
        if (Apple_Collision(head_x, head_y, Apples[i].x, Apples[i].y)) {
            for (j = *SnakeLength - 1; j > 0; j--) {
                ChoisirCouleurDessin(back_color); /* permet de corriger partiellement le bug du pixel en x=0, y=0 */
                RemplirRectangle(0, 0, 15, 15);
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
        ChargerImage("apple.png", Apples[i].x, Apples[i].y, 0, 0, 15, 15);
    }
}
void Update_Score() {
    char score_str[15];
    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(score_str, "Score: %06d", score);
    EcrireTexte(WindowWidth- 200, WindowHeight - 100, score_str, 2);
}

void GameOverScreen() {
    ChargerImageFond("gameover.png"); /* à changer */
    /*
    EcrireTexte(350, 600, "Game Over", 2);  
    EcrireTexte(300, 650, "Appuyez sur Echap pour quitter", 2); */
    while (Touche() != XK_Escape) {} 
}


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

        if (snake[0].x < 15 || snake[0].x >= 900 || snake[0].y < 15 || snake[0].y >= 600) {
            go_on = 0;
        }

         if (Snake_Self_Collision(snake, SnakeLength) || Snake_OutOfBounds(snake[0].x, snake[0].y)) {
            go_on = 0;
            GameOverScreen();

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