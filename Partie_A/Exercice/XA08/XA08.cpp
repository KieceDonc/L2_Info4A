#include <stdio.h>

int recursionCmpt = 0;
int lgSurn(int n){
  recursionCmpt++;
  if(n<=1){
    return recursionCmpt;
  }
  if(!(n%2==0)){
    return lgSurn(3*n+1);
  }else{
    return lgSurn(n/2); 
  }
}

int main(){
  printf("%d\n",lgSurn(8));
  return 0;
}