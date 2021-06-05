#include <stdio.h>
#include <cstring>

/*
Réalisez une fonction nommée altStrcat qui fait
exactement la même chose que Strcat mais sans faire
d'appel à d'autres fonctions.
*/

void altStrcat(char str0[], char str1[]){
  int indexStart = 0;
  int shouldContinue = 1;
  do{
    shouldContinue = str0[indexStart]!=0;
    if(shouldContinue){
      indexStart++;
    }
  }while(shouldContinue);
  
  int indexEnd = 0;
  shouldContinue = 1;
  do{
    shouldContinue = str1[indexEnd]!=0;
    if(shouldContinue){
      indexEnd++;
    }
  }while(shouldContinue);
  indexEnd+=indexStart;

  for(int index=indexStart;index<indexEnd;index++){
    str0[index]=str1[index-indexStart];   
  }
}

int main(){
  char str0[10] = "oui";
  char str1[] = "non";
  altStrcat(str0,str1);
  printf("%s\n",str0);
  return 0;
}