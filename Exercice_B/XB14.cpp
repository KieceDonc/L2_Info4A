#include <stdio.h>

int exg(int mot,int i,int j){
  int bi = (mot & 1<<i)>>i; // on récupère le bit à la position i
  int bj = (mot & 1<<j)>>j; // on récupère le bit à la position j 
  mot = mot & ~(1<<i); // on met le bit à 0 à la position i
  mot = mot & ~(1<<j); // on met le bit à 0 à la position j
  mot = mot | bj<<i; // on affecte le bit j à la position i
  mot = mot | bi<<j; // on affecte le bit i à la position j
  return mot;
}

int main(){
  printf("%d\n",exg(5,2,1));
  return 0;
}