#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LARGEUR 20 // Largeur de la zone de jeu
#define HAUTEUR 20 // Huatuer de la zone de jeu
#define VIDE 0
#define SNAKE 1 // Taille du serpent au départ
#define FRUIT 2 // Taile des fruits

int GameOver;
int Score;
int SerpX, SerpY; // Position de la tête du serpent
int FruitX, FruitY; // Position du fruit
int longueur; 
int queueX[100], queueY[100]; // Position de la queue du serpent

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void initialiser() {
    gameOver = 0;
    dir = STOP;
    SerpX = LARGEUR / 2; // Placement au centre du tableau
    SerpY = HAUTEUR / 2; // "                              "
    FruitX = rand() % LARGEUR; // Valeur random pour le placement des fruits
    FruitY = rand() % HAUTEUR; // "                                         "
    score = 0; // Valeur du score au départ
    longueur = 1; // Longueur du serpent évolutive
}

void dessiner() {
    system("clear");
    for (int i = 0; i < LARGEUR + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (j == 0)
                printf("#");
            if (i == SerpY && j == SerpX)
                printf("O");
            else if (i == FruitY && j == FruitX)
                printf("F");
            else {
                int estQueue = 0;
                for (int k = 0; k < longueur; k++) {
                    if (queueX[k] == j && queueY[k] == i) {
                        printf("o");
                        estQueue = 1;
                    }
                }
                if (!estQueue)
                    printf(" ");
            }
            if (j == LARGEUR - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < LARGEUR + 2; i++)
        printf("#");
    printf("\n");
    printf("Score : %d\n", score);
}

void input() {
    if (_kbhit()) { // Définition de la détection des touches du clavier
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void logique() {
    int prevX = queueX[0];
    int prevY = queueY[0];
    int prev2X, prev2Y;
    queueX[0] = SerpX;
    queueY[0] = SerpY;

    for (int i = 1; i < longueur; i++) {
        prev2X = queueX[i];
        prev2Y = queueY[i];
        queueX[i] = prevX;
        queueY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) { // Action lorsque les différentes touches sont declenchées
        case LEFT:
            SerpX--;
            break;
        case RIGHT:
            SerpX++;
            break;
        case UP:
            SerpY--;
            break;
        case DOWN:
            SerpY++;
            break;
        default:
            break;
    }

    if (SerpX >= LARGEUR || SerpX < 0 || SerpY >= HAUTEUR || SerpY < 0) { // Action lorsque le serpent est hors-zone
        gameOver = 1;
    }

    for (int i = 0; i < longueur; i++) { // Action lorsque le serpent se mord 
        if (queueX[i] == SerpX && queueY[i] == SerpY) {
            gameOver = 1;
        }
    }

    if (SerpX == FruitX && SerpY == FruitY) { // Apparition d'un nouveau fruit si fruit avalé
        score += 10;
        FruitX = rand() % LARGEUR;
        FruitY = rand() % HAUTEUR;
        longueur++;
    }
}

int main() { // Programme principal à décaler dans un fichier main
    srand(time(NULL));
    initialiser();
    while (!gameOver) {
        dessiner();
        input();
        logique();
        usleep(100000);
    }
    return 0;
}
