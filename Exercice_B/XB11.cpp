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
  int x = 16+8;
  printf("%d\n",x%16);
  printf("%d\n",divPar16(x));
  printf("%d\n",x>>4);
  return 0;  
}