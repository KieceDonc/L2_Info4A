#include <stdio.h>

int ecritBit(int data,int position,int bit){
  int masque = 1 << position;
  if(bit){
    return data | masque;
  }else{
    return data & (~masque);
  }
}
int main(){
  printf("%d\n",ecritBit(0xABCD,5,0));
  printf("%d\n",ecritBit(0xABCD,6,0));
  printf("%d\n",ecritBit(0xABCD,10,1));
  printf("%d\n",ecritBit(0xABCD,11,1));
  return 0; 
}