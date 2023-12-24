#include "game.h"
#include <graph.h>
#include <stdio.h>
#define CYCLE 100000L

unsigned long debutJeu;
unsigned long suivant;


/* Attends le temps spécifié en microsecondes */
void Timer(unsigned long us) {
    unsigned long attente = Microsecondes() + us;
    while (Microsecondes() < attente) {}
}


/* Retourne le temps écoulé depuis le début du jeu en microsecondes */
unsigned long MicrosecondesDepuisDebut() {
    return Microsecondes() - debutJeu;
}

/*  Retourne le temps écoulé depuis le début du jeu en secondes */
unsigned long SecondesDepuisDebut() {
    return MicrosecondesDepuisDebut() / 1000000L;
}

/* Initialise le temps de début du jeu */
void debut(){
    debutJeu = Microsecondes();
    suivant = debutJeu + CYCLE;
}

/* Retourne le temps suivant */

unsigned long getsuivant(){
   return suivant; 
}
/*  Définit le temps suivant */
void setsuivant(){
    suivant = Microsecondes() + CYCLE;
}
/* Retourne le temps de début du jeu */
unsigned long getdebutJeu(){
    return debutJeu;
}