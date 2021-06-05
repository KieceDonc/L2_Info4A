#include <stdio.h>

void number(int x){
  printf("%d\n",x&~0<<4|0);
}

int main(){
  number(31);
  return 0;
}