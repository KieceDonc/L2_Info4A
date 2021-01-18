#include <stdio.h>

int why(int n){
  int result = 0;
  for(int x=0;x<=n;x++){
    result+=x;
  }
  return result;
}

int main(){
  for(int x=1;x<=10;x++){
    printf("%d\n",why(x));
  }
  return 0;
}