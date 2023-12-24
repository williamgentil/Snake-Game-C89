#include <graph.h>
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "apple.h"

int WindowWidth = 930;
int WindowHeight = 750;

/* Fonction pour afficher le menu principal*/


int Screen_Menu() {
    InitialiserGraphique();
    CreerFenetre(10, 10, WindowWidth, WindowHeight);
    ChargerImageFond("snake-screenmenu.png");
    ChargerImage("green-arrow.png", 10, 420, 0, 0, 125, 70); /* not working */
    
    /* Boucle d'attente des clics de souris pour la sélection des options*/
    while (1) {
        if (SourisCliquee()) {
            int x = _X;
            int y = _Y;
            if ((x >= 100 && x <= 500) && (y >= 450 && y <= 550)) {
                ChoisirEcran(0);
                break;
            } else if ((x >= 710 && x <= 1050) && (y >= 370 && y <= 470)) {
                FermerGraphique();
                return EXIT_SUCCESS;
            }
        }
    }
}


/* Fonction pour afficher l'arrière-plan */

int Background() {
    int back_color = CouleurParComposante(140, 25, 0);
    ChoisirCouleurDessin(back_color);
    RemplirRectangle(0, 0, WindowWidth, WindowHeight);
}

/* Fonction pour afficher le terrain de jeu avec le serpent */

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

/* Fonction pour afficher l'écran de fin de jeu */

int GameOverScreen() {
    ChargerImageFond("gameover.png");
    Update_Score();
    while (1) {
        if (SourisCliquee()) {
            int x = _X;
            int y = _Y;
            if ((x >= 100 && x <= 500) && (y >= 480 && y <= 500)) {
                ChoisirEcran(0);
                break;
            } else if ((x >= 710 && x <= 1050) && (y >= 370 && y <= 470)) {
                FermerGraphique();
                return 0;
            }
        }
    }
}

/* Fonction pour mettre à jour le score affiché */

void Update_Score() {
    char score_str[15];
    int back_color = CouleurParComposante(140, 25, 0);

    ChoisirCouleurDessin(back_color);
    RemplirRectangle(WindowWidth - 230, WindowHeight - 120, 150, 50);

    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(score_str, "Score: %06d", score);
    EcrireTexte(WindowWidth - 210, WindowHeight - 100, score_str, 2);
}


/* Fonction pour afficher les touches de contrôle */

void Keys() {
    ChargerImage("escape-key.png", 25, WindowHeight-75, 0, 0, 200, 45);
    ChargerImage("spacebar-key.png", 270, WindowHeight-75, 0, 0, 383, 45);
    ChargerImage("arrows.png", 700, WindowHeight-75, 0, 0, 196, 45);

}
