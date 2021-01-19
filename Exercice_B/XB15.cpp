#include <stdio.h>
#include <math.h>

int xorMasque(unsigned data, unsigned masque){
  int puissance = ceil(sqrt(masque));
  do{
    int bitP = masque & 1 << puissance;
    if((bitP>>puissance)){ // permet de savoir si le bit à la position "puissance" est égale à 0 ou 1. Si égale à 1 on rentre dans le if
      data = data | bitP;
    }
    puissance--;
  }while(puissance>=0);
  return data;
}
int main(){
  printf("%d\n",xorMasque(32,2));
  return 0;
}