#include <stdio.h>

int main(){
  int z = 7;
  int* q = &z;
  int** p = &q;
  printf("%d\n",**p);
  **p = 0;
  printf("%d\n",**p);
  printf("%d\n",z);
  return 0;
}