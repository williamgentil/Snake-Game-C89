#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
void window(){
   int Length=60, Heigth=40;
   int WindowMargin=10, WindowLength=32*Length, WindowHeigth=25.5*Heigth;
   int GameScreenMarginX=Length, GameScreenMarginY=WindowMargin+Heigth;
   int GameScreenLength=WindowLength-2*GameScreenMarginX, GameScreenHeigth=WindowHeigth-3*GameScreenMarginY;
   InitialiserGraphique();
   CreerFenetre(WindowMargin, WindowMargin, WindowLength, WindowHeigth);
   couleur c;
   c=CouleurParNom("black");
   EffacerEcran(c);
   ChoisirCouleurDessin(CouleurParNom("white"));
   EcrireTexte(WindowLength/2.15, Heigth, "Snake", 2);
   ChoisirCouleurDessin(CouleurParComposante(157, 207, 31));
   RemplirRectangle(GameScreenMarginX, GameScreenMarginY, GameScreenLength, GameScreenHeigth);
   Touche();
   FermerGraphique();
   return;
}
void apple(){
   FILE *apple;
   apple=fopen("Apple_JE3_BE3.png", "w");
   ChargerImage(apple, 0, 0, 0, 0, 0, 0); //<- Pose un problème pour l'instant
   Touche();
   fclose(apple);
   return;
}
int main(void)
{ 
   return 0;
}
   