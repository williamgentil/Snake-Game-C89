#include <stdio.h>
#include <unistd.h>

void afficherBarreDeChargement(int total, int progression) {
    const int longueurBarre = 50;
    int pourcentage = (progression * 100) / total;
    int numBarres = (progression * longueurBarre) / total;

    printf("[");
    for (int i = 0; i < longueurBarre; ++i) {
        if (i < numBarres) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\r", pourcentage);
    fflush(stdout);
}

int main() {
    const int total = 100;

    for (int i = 0; i <= total; ++i) {
        afficherBarreDeChargement(total, i);
        usleep(30000); // Pause de 30000 microsecondes (0.03 seconde)
    }
    printf("\nChargement terminé!\n");

    return 0;
}





