#include <stdio.h>
#include <math.h>

int max1(int x){
  int puissance = sqrt(x); 
  int max=0;
  int currentMax=0;
  do{ 
    int current = x & (1<<puissance);
    printf("%d %d\n",puissance,current);
    if(current){
      currentMax+=1;
      if(currentMax>max){
        max = currentMax;
      }
    }else{
      currentMax=0;
    }
    puissance-=1;
  }while(puissance>=0);
  return max;  
}

int main(){
  printf("%d\n",max1(0b1101111));
  return 0;
}