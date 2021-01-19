#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* fillRand(int* tab, int n, int k){
  for(int x=0;x<n;x++){
    srand(x);
    int random = ((double) rand())/RAND_MAX*k; //*k;
    tab[x]=random;
  }
  return tab;
}

int main(){
  int tab[10];
  int* tabr = fillRand(&tab[0],10,10);
  for(int x=0;x<10;x++){
    printf("%d\n",tabr[x]);
  }
  return 0;
}