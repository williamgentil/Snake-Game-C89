#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int main()
{ 
   FILE* apple;
   apple=fopen("item 2-1.png.png", "r");
   int Length=60, Heigth=40;
   int WindowMargin=10, WindowLength=30*Length, WindowHeigth=30*Heigth;
   InitialiserGraphique();
   CreerFenetre(WindowMargin, WindowMargin, WindowLength, WindowHeigth);
   couleur c;
   c=CouleurParNom("black");
   EffacerEcran(c);
   ChoisirCouleurDessin(CouleurParNom("white"));
   EcrireTexte(WindowLength/3, Heigth, "Snake", 2);
   ChoisirCouleurDessin(CouleurParComposante(110, 207,39));
   RemplirRectangle(20, 50, 1240, 800);
   Touche();
   FermerGraphique();
   return EXIT_SUCCESS;
   //Fonction temps en temps réel 
   /*on marque le debut du cycle 
   suivant= Microsecondes()+CYCLE;
   while (...) /* boucle principale du programme 
   {
	if (Microsecondes()>suivant)
	{
		/* une periode s'est écoulé 
		/* prochaine date 
		suivant= Microsecondes()+CYCLE;

}
   }*/
}