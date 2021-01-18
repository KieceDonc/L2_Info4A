#include <stdio.h>

void printB2(int value, int nBits){
  unsigned masque = 1 << (nBits-1);
  while(masque > 0){
    if(masque & value){
      printf("1");
    }else{
      printf("0");
    }
    masque = masque >> 1;
  }
}

int main(){
  return 0;
}