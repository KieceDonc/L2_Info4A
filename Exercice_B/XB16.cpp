#include <stdio.h>
#include <math.h>

int seek(unsigned data, unsigned seq, unsigned n){
  if(seq>data){
    return false;
  }
  seq = seq & 1<<n;
  int puissance = (int)sqrt(data);
  do{
    int bits = data>>(n-puissance) & 1<<n;
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
  printf("%d\n",seek(31,4,2));
  return 0;
}