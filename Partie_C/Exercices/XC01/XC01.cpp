#include <stdio.h>

int main(){
  int x=10;
  int* p =&x;
  *p = *p + 1;
  printf("%d\n",x);
  return 0;
}