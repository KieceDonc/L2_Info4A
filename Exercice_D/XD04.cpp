#include <stdio.h>
#include <cstring>

/*
Réalisez une fonction nommée altStrlen qui fait
exactement la même chose que Strlen mais sans
faire d'appel à d'autres fonctions.
*/
int altStrlen(char str[]){
  int shouldContinue = 1;
  int cmpt = 0;
  do{
    shouldContinue = str[cmpt]!=0;
    if(shouldContinue){
      cmpt++;
    }
  }while(shouldContinue);
  return cmpt;
}

int main(){
  char str[10] = "abced";
  printf("%d\n",altStrlen(str));
  return 0;
}