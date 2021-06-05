#include <stdio.h>
#define K 1000

int seekDup0(int* tab,int n){
  for(int x = 0;x<n;x++){
    if(tab[x]<=K){
      for(int y = 0;y<n;y++){
        if(tab[y]<=K && x!=y && tab[x]==tab[y]){
          return 1;
        }
      }
    }
  }
  return 0;
}


int seekDup1(int* tab,int n){
  int save[K] = {};
  for(int x=0;x<n;x++){
    if(tab[x]<=K){
      save[tab[x]]+=1;
      if(save[tab[x]]>=2){
        return 1;
      }
    }
  } 
  return 0;
}

int main(){
  int length = 10;
  int tab[length]={0,20000,200,20,1,2,3,4,5,9};
  printf("%d\n%d\n",seekDup1(tab,length),seekDup0(tab,length));
  return 0;
}