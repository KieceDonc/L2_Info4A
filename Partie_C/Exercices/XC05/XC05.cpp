#include <stdio.h>

int main(){
  int tab[10]= {1,2,3,4,5,6};
  int* p = tab + 2;
  p[2]=-1;
  p=p+2;
  *p=9;
  for(int x=0;x<10;x++){
    printf("%s%d %s %d\n","valeur n°",x,"=",tab[x]);
  }
  return 0;
}