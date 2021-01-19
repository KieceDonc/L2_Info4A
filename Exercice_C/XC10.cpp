#include <stdio.h>

void rotaG(int* tab,int n){
  for(int x=0;x<(int)(n/2);x++){
    int left = tab[x];
    int right = tab[n-1-x];
    tab[n-1-x] = left;
    tab[x] = right;
  }
}

void printTab(int* tab,int length){
  for(int x=0;x<length;x++){
    printf("%s%d %s %d\n","index n°",x,"=",tab[x]);
  }
}

int main(){
  int length = 10;
  int tab[length] = {0,1,2,3,4,5,6,7,8,9};
  rotaG(tab,length);
  printTab(tab,length);
  return 0;
}

