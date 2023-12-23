#include "game.h"
#include <graph.h>
#include <stdio.h>
#define CYCLE 100000L

/* unsigned long debutJeu,suivant; */

unsigned long int debutJeu = Microsecondes();
unsigned long  int suivant = Microsecondes() + CYCLE;

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

