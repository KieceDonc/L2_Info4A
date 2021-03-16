#include <stdio.h>
#include <stdlib.h>

int* fillRand(int* tab, int n, int k){
  for(int x=0;x<n;x++){
    srand(x+x%2+7);
    int random = ((double) rand())/RAND_MAX*k; // entre 0 et k-1 inclus
    tab[x]=random;
  }
  return tab;
}

int main(){
  int tab[10] = {0};
  int* tabr = fillRand(tab,5,10);
  for(int x=0;x<10;x++){
    printf("%d\n",tabr[x]);
  }
  return 0;
}