#include <stdio.h>

int masquen1(int n){
  int save = n;
  n = ~0;
  n = n << save;
  return ~n; 
}

unsigned int divPar16(int x)
{
    return x & masquen1(4);
}

int main(){
  printf("%d\n",18>>4);
  return 0;  
}