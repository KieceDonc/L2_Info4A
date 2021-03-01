#include <stdio.h>

#define NMAX 10

typedef struct 
{
  int n;
  double data[NMAX];
}carnet;

void ajoute(carnet* c,double note){
  c->data[c->n] = note;
  c->n+=1;
}

double moyenne(carnet* c){
  double tc = 0;
  for(int x=0;x<c->n;x++){
    tc+=c->data[x];
  }
  return tc/c->n;
}

void printNotes(carnet* c){
  for(int x=0;x<c->n;x++){
    printf("note n°%d = %f\n",x,c->data[x]);
  }
}

int main(){
  carnet c = {2,{10.0,15.0}};
  ajoute(&c,17.5);
  printf("%f\n",moyenne(&c));
  printNotes(&c);
  return 0;
}