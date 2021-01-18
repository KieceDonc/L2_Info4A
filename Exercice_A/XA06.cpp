#include "stdio.h"

void whileVersion(){
  printf("%s\n","-------------------------");
  printf("%s\n","while version:");
  int i=5;
  do{
    printf("%d",i); 
    i-=1;
  }while(i>=0);
  printf("\n");
}

void forVersion(){
  printf("%s\n","-------------------------");
  printf("%s\n","for version:");
  for(int i=5;i>=0;i--){
    printf("%d",i);
  }
  printf("\n");
}

int main(){
  forVersion();
  whileVersion();
  return 0;
}