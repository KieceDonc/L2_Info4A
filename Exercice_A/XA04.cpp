#include <stdio.h>
#include <stdlib.h>

double getRand(){
  return ((double) rand())/RAND_MAX;
}

int main(){
  printf("%f",getRand());  
  return 0;
}