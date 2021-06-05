#include <stdio.h>

/*
Réalisez une fonction nommée fusion en accepte en paramètres :
un pointeur sur int tabl désignant un tableau d'entiers,
un entier nl représentant la longueur du tableau désigné par tab1,
un pointeur sur int tab2 désignant un tableau d'entiers,
un entier n2 représentant la longueur du tableau désigné par tab2,
et qui retourne un tableau dynamique de longuer nl + n2 contenant les éléments de 
tab1 suivis de ceux de tab2
*/

int* fusion(int* tab1, int n1, int* tab2, int n2){
  int* tab3 = new int[n1+n2];
  for(int x=0;x<n1;x++){
    tab3[x]=tab1[x];
  }
  for(int x=0;x<n2;x++){
    tab3[n1+x]=tab2[x];
  }
  return tab3;
}

void printTab(int* tab,int length){
  for(int x=0;x<length;x++){
    printf("%s%d %s %d\n","index n°",x,"=",tab[x]);
  }
}

int main(){
  int n1 = 5;
  int* tab1 = new int[n1];
  int n2 = 7;
  int* tab2 = new int[n2];

  for(int x=0;x<n1;x++){
    tab1[x]=x*3;
  }
  for(int x=0;x<n2;x++){
    tab2[x]=x*4;
  }
  int* tab3 = fusion(tab1,n1,tab2,n2);
  printTab(tab3,n1+n2);
  return 0;
}