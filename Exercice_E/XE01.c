#include <stdio.h>
#include <stdlib.h>

/*
Donnez les lignes de code permettant
- de créer un tableau dynamique de 6 cellules pouvant contenir chacune un double.

- de créer un tableau dynamique de 2 cellules contenant chacune un pointeur sur
double.

- de placer dans la première cellule du deuxième tableau l'adresse de la première
cellule du premier et dans la deuxième cellule du deuxième tableau l'adresse de la
dernière cellule du premier.

- de libérer la mémoire occupée par les deux tableaux.
*/

int main(){
  double* t1 = (double*)calloc(6,sizeof(double));
  double** t2 = (double**)calloc(2,sizeof(double*));
  t2[0] = &(t1[0]);
  t2[1] = &(t1[5]);
  free(t1);
  free(t2);
  return 0;
}