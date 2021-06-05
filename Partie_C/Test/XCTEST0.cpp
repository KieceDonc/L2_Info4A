#include <stdio.h>

int main(){
  int tab[100] = {1,2,3,4,5,6};
  tab[7] = 333;
  int* p = tab;
  int* q = tab+2;
  printf("%d %d %d %d\n",tab[3],p[3],q[3],tab[1000]);
  return 0;
}