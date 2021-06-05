#include <stdio.h>
#include <math.h>

int max1(int x){
  int puissance = (int)sqrt(x);
  int maxConsecutif = 1;
  int consecutif = 0;
  do{
    if((x - (1<<puissance))>=0){
      x-=(1<<puissance);
      consecutif++;
      if(consecutif>maxConsecutif){
        maxConsecutif = consecutif;
      }
    }else{
      consecutif = 0;
    }
    puissance--;
  }while(puissance>=0);
  return maxConsecutif;
}

int main(){
  printf("%d\n",max1(44));
  return 0;  
}