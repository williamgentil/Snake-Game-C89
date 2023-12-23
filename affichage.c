#include <graph.h>
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

extern int score;
int WindowWidth = 930;
int WindowHeight = 750;

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

void GameOverScreen() {
    ChargerImageFond("gameover.png"); /* à changer */
    /*
    EcrireTexte(350, 600, "Game Over", 2);  
    EcrireTexte(300, 650, "Appuyez sur Echap pour quitter", 2); */
    while (Touche() != XK_Escape) {} 
}

void Update_Score() {
    char score_str[15];
    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(score_str, "Score: %06d", score);
    EcrireTexte(WindowWidth- 200, WindowHeight - 100, score_str, 2);
}