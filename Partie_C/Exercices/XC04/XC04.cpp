#include <stdio.h>

void setTo0(int* p){
  *p = 0;
}

int main(){
  int x = 10;
  setTo0(&x);
  printf("%d\n",x);
  return 0;
}