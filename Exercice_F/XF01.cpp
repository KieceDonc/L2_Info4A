#include <stdio.h>

/*
Déclarez une structure date avec un champ jour de type char, un champ mois
de type char et un champ annee de type int. (Noubliez pas que le type char
permet de représenter des entiers.)
Définissez une fonction test qui :
- déclare une variable de type date et l'initialise avec une instance de date représentant le premier janvier 1900,
- modifie le champ annee de la variable d en remplaçant sa valeur par 2000,
- affiche la valeur du champ mois en utilisant la fonction printf.
*/

typedef struct{
  char jour;
  char mois;
  int annee;
}Date;

void test(){
  Date date = {'l','j',1900};
  date.annee = 2000;
  printf("%c",date.mois);
}

int main(){
  test();
  return 0;
}