#include "stdio.h"

void whileVersion(){
  printf("%s\n","-------------------------");
  printf("%s\n","while version:");
  int i=5;
  int j=0;
  do{
    do{
      printf("{%d,%d}",i,j);
      printf("\n");
      j+=1;
    }while(j<i);
    j=0;
    i-=1;
  }while(i>=0);
  printf("\n");
}

void forVersion(){
  printf("%s\n","-------------------------");
  printf("%s\n","for version:");
  for(int i=5;i>=0;i--){
    for(int j=0;j<i;j++){
      printf("{%d,%d}",i,j);
      printf("\n");
    }
  }
  printf("\n");
}

int main(){
  forVersion();
  whileVersion();
  return 0;
}