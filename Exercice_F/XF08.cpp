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
  carnet c1 = {0,{10.0,15.0}};
  ajoute(&c1,17.5);
  ajoute(&c1,18.5);
  ajoute(&c1,10.5);
  carnet c2 = c1;
  ajoute(&c2,9);
  printf("moyenne = %f\n",moyenne(&c2));
  printNotes(&c1);
  return 0;
}