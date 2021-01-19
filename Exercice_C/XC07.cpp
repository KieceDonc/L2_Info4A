#include <stdio.h>

int main(){
  int p[10] = {0};
  int* q = p+3;
  *q = 9;
  printf("%d\n",p[3]);
  return 0;
}