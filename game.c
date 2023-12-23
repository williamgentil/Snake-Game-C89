#include "game.h"
#include <graph.h>
#include <stdio.h>
#define CYCLE 100000L

unsigned long debutJeu;
unsigned long suivant;

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

void debut(){
    debutJeu = Microsecondes();
    suivant = debutJeu + CYCLE;
}

unsigned long getsuivant(){
   return suivant; 
}

void setsuivant(){
    suivant = Microsecondes() + CYCLE;
}

unsigned long getdebutJeu(){
    return debutJeu;
}