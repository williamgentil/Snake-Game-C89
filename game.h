#ifndef GAME_H
#define GAME_H

extern unsigned long debutJeu;
extern unsigned long suivant;

void Timer(unsigned long us);
void AfficherTemps(unsigned long tempsDebut);
unsigned long MicrosecondesDepuisDebut();
unsigned long SecondesDepuisDebut();
void debut();
unsigned long getsuivant();
void setsuivant();
unsigned long getdebutJeu();

#endif