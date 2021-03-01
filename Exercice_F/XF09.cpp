#include <stdio.h>

#define NMAX 10

class Carnet{
  private :
    int n;
    double data[NMAX];

  public :
    Carnet(){
      this->n = 0;
    };

    void ajoute(int note){
      this->data[this->n] = note;
      this->n+=1;
    };

    double moyenne(){
      double tc = 0;
      for(int x=0;x<this->n;x++){
        tc+=this->data[x];
      }
      return tc/this->n;
    };

    void print(){
      for(int x=0;x<this->n;x++){
        printf("note n°%d = %f\n",x,this->data[x]);
      }      
    };
};

int main(){
  return 0;
}