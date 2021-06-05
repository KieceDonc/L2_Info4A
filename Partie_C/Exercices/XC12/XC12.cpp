#include <stdio.h>

void minMaxTab(double* tab,int n,double* min,double* max){
  for(int x=0;x<n;x++){
    double value = tab[x];
    *min = value<*min ? value : *min;
    *max = value>*max ? value : *max;
  }
}

void printTab(double* tab,int length){
  for(int x=0;x<length;x++){
    printf("%s%d %s %f\n","index n°",x,"=",tab[x]);
  }
}

int main(){
  int length = 10;
  double tab[length] = {-0.5236,1,2,3,4,5,6,7,8,9};
  double min=0;
  double max=0;
  printTab(tab,length);
  minMaxTab(tab,length,&min,&max);
  printf("%s%f\n%s%f\n","min=",min,"max=",max);
  return 0;
}

