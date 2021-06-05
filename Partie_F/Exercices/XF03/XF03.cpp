#include <stdio.h>

/*
Réalisez une fonction bary acceptant en paramètres :
  - un pointeur sur point tab désignant un tableau d'instances de point,
  - un entier n supposé avoir pour valeur la longueur du tableau désigné par tab.

La fonction bary doit retourner une instance de point représentant le barycentre des
points du tableau désigné par tab.

Le barycentre d'un ensemble de point a pour coordonnée x la moyenne des coordonnées x 
des points de cet ensemble et pour coordonnée y la moyenne de leurs coordonnées y.
*/

class Point{
  private:
    double x;
    double y;

  public:
    Point(double x, double y){
      this->x = x;
      this->y= y;
    };

    Point(){
      this->x = 0;
      this->y= 0;
    };

    double getX(){
      return this->x;
    };

    double getY(){
      return this->y;
    };

    void setX(double x){
      this->x = x;
    };

    void setY(double y){
      this->y = y;
    };
};

Point bary(Point tab[], int length){
  double Ptx=0;
  double Pty=0;
  for(int x=0;x<length;x++){
    Ptx+=tab[x].getX();
    Pty+=tab[x].getY();
  }
  Ptx=Ptx/length;
  Pty=Pty/length;

  return Point(Ptx,Pty);
}

int main(){
  Point tab[] = {Point(1,1),Point(5,6),Point(4,2),Point(1.2,0.33)};
  Point barycentre = bary(tab,4);
  printf("%f %f\n",barycentre.getX(),barycentre.getY());
  return 0;
}