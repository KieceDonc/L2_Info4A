#include <stdio.h>
#include <math.h>

int seek(unsigned data, unsigned seq, unsigned n){
  if(seq>data){
    return false;
  }
  seq = seq & ~(~0<<n);
  int puissance = ceil(sqrt(data));
  do{
    int bits = data>>(n-puissance) & ~(~0<<n);
    printf("%d",bits);
    printf("%s"," -- ");
    printf("%d\n",seq);
    if(bits == seq){
      return true;
    }
    puissance--;
  }while(puissance>=n);
  return false;
}

int main(){
  printf("%d\n",seek(13,5,3));
  return 0;
}