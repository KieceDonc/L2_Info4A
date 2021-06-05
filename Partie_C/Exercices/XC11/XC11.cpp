#include <stdio.h>

int isIN(int* tab,int n,int val){
  int founded = 0;
  int index = 0;
  do{
    founded = tab[index]==val;
    index++;
  }while(!founded && index<n);
  return founded;
}

void printTab(int* tab,int length){
  for(int x=0;x<length;x++){
    printf("%s%d %s %d\n","index n°",x,"=",tab[x]);
  }
}

int main(){
  int length = 10;
  int tab[length] = {0,1,2,3,4,5,6,7,8,9};
  printf("%d\n",isIN(tab,length,9));
  printTab(tab,length);
  return 0;
}

