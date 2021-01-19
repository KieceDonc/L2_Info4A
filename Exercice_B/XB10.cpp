#include <stdio.h>

int masquen1(int n){
  int save = n;
  n = ~0;
  n = n << save;
  return ~n; 
}

int main(){
  printf("%d\n",masquen1(2));
  return 0;
}