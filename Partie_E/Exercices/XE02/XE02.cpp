#include <stdio.h>

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
  double* tab1 = new double[6];
  double** tab2 = new double*[2];
  tab2[0] = &tab1[0];
  tab2[1] = &tab1[5];

  delete[] tab1;
  delete[] tab2;
  return 0;
}