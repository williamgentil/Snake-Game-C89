#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

void apple(){
   FILE *apple;
   apple=fopen("Apple_JE3_BE3.png", "w");
   ChargerImage(apple, 0, 0, 0, 0, 0, 0); //<- Pose un problème pour l'instant
   Touche();
   fclose(apple);
   return;
}

int main(){
    apple();
    return 0;
}