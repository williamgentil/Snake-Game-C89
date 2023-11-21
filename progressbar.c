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
        usleep(100000); // Pause de 100 000 microsecondes (0.1 seconde)
    }
    printf("\nChargement terminé!\n");

    return 0;
    /*void progressbar(int percentage) {
    printf("[");
    int i;
    for (i = 0; i < percentage / 2; i++) {
        printf("\U+0001F40D"); 
    }
    for (i; i < 50; i++) {
        printf(" ");
    }
    printf("] %d%%\r", percentage);
    fflush(stdout);
}

int main() {
    int percentage = 0;


    while (percentage <= 100) {
        progressbar(percentage);
        usleep(30000); 
        percentage += 2; 
    }

    printf("\nLancement du jeu\n");
    printf("Le logo de notre jeu : \n\n\n")
    printf("/^\\/^\\ 
         _|__|  O|
\\/     /~    \\_/ \
 \\____|__________/  \
       \\_______      \
                `\\     \\                 \
                  |     |                  \
                 /      /                    \
                /     /                       \\
              /      /                        \\ \
             /     /                           \\  \
           /     /             _----_           \\   \
          /     /           _-~      ~-_         |   |
         (      (        _-~    _--_    ~-_     _/   |
        \\      ~-____-~    _-~    ~-_    ~-_-~    /
            ~-_           _-~          ~-_       _-~
               ~--______-~                ~-___-~")

    return 0;
}*/
}





