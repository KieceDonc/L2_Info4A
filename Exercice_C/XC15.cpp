#include <stdio.h>
#define K 1000

/*
Le but de cet exercice est de développer des fonctions permettant de gérer des ensembles d'entiers. On supposera, pour des raisons pratiques
d'efficacité de la représentation utilisée, que les valeurs des éléments de ces ensembles sont comprisent entre O et une constante K qui sera
arbitrarement fixée à 1000 :

#define K 1000

Un ensemble est représenté par un tableau de K+1 Booléens (techniquement par un tableau d'entiers pouvant prendre la valeur O (false) ou 1 (true).

Le principe de la représentation est le suivant : soit E un ensemble et tabE sa représentation telle que décrite ci-dessus. Un entier x appartient à E si et
seulement si tabE[x] vaut 1.

Donc par exemple l'ensemble vide { } a pour représentation un tableau de 1001 cellules contenant toutes des O0. L'ensemble {3, 7} a pour représentation
un tableau de 1001 cellules contenant toutes des O sauf celles d'indice 3 et 7 qui contiennent 1.

Vous devez réaliser les fonctions suivantes :

— void add(int* tabE, int x) qui ajoute x à l'ensemble représenté par tabE (sans effet si x était déjà dans l'ensemble).

— int isin(int* tabE, int x) qui retrourne true (1) si x est élément de l'ensemble représenté par tabE et false (0) dans le cas contraire.

-— void setInter(int* tabA, int* tabB, int* tabI) qui place dans tabl le résultat de l'intersection des ensembles représentés par tabA et tabB.

— void setUnion(int* tabA, int* tabB, int* tabU) qui place dans tabU le résultat de l'union des ensembles représentés par tabA et tabB.

— void printSet(int* tabE) qui affiche sous une forme lisible les éléments de l'ensemble représenté par tabE.
*/

void add(int* tabE, int x){
  tabE[x]=1;
}

int isin(int* tabE,int x){
  return tabE[x];
}

void setInter(int* tabA, int* tabB, int* tabI){
  for(int x=0;x<K;x++){
    tabI[x] = tabA[x] && tabB[x];
  }
}

void setUnion(int* tabA, int* tabB, int* tabU){
  for(int x=0;x<K;x++){
    tabU[x] = tabA[x] || tabB[x];
  }
}

void printSet(int* tabE,int maxIndexToPrint){
  for(int x=0;x<=maxIndexToPrint;x++){
    printf("%s%d %s %d\n","index n°",x,"=",tabE[x]);
  }
}

int main(){
  int tabA[K] = {1,1,1,1,1,1,1,1}; // [0;7]
  int tabB[K] = {0,0,0,0,0,0,1,1,1,1,1}; // [6;10]
  
  add(tabB,11); // [6;11]
  printf("%d\n",isin(tabB,11)); // 1 true
  printf("%d\n",isin(tabB,12)); // 0 false

  int tabI[K] = {};
  int tabU[K] = {};

  setInter(tabA,tabB,tabI); // [6;7]
  printSet(tabI,20);

  setUnion(tabA,tabB,tabU); // [0;11]
  printSet(tabU,20);
  return 0;
}