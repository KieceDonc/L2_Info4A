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
  bool founded = false;
  int k = 5;
  int n = 0;
  do{
    n++;
    founded = (lgSurn(n)>=k);
  }while(!founded);
  printf("%d\n",n);
  return 0;
}