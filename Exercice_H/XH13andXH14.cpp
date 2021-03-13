#include <stdio.h>
#include <math.h>

#define MAX_SOM 5

class Point{
  private:
    double x;
    double y;

  public:
    Point(double x, double y);

    Point();

    double getX();
    double getY();
    void setX(double x);
    void setY(double y);

    Point milieu(Point& autre);

    void print();
};

Point::Point(double x, double y){
  this->x = x;
  this->y= y;
};

Point::Point(){
  this->x = 0;
  this->y= 0;
};

double Point::getX(){
  return this->x;
};

double Point::getY(){
  return this->y;
};

void Point::setX(double x){
  this->x = x;
};

void Point::setY(double y){
  this->y = y;
};

Point Point::milieu(Point& autre){
  double Ptx=this->x; 
  double Pty=this->y;
  Ptx+=autre.x;
  Pty+=autre.y;
  Ptx=Ptx/2;
  Pty=Pty/2;
  return Point(Ptx,Pty);
};

void Point::print(){
  printf("x = %f, y = %f\n",this->x,this->y);
};

class Segment{
  private:
    Point a;
    Point b;

  public:
    Segment();

    Segment(double x1,double y1,double x2,double y2);

    Point milieu();

    double longeur();

    void print();
};

Segment::Segment() : a(0,0),b(0,0){

};

Segment::Segment(double x1,double y1,double x2,double y2) : a(x1,y1),b(x2,y2){

};

double Segment::longeur(){
  int a = pow((this->b.getX()-this->a.getX()),2)+pow((this->b.getY()-this->a.getY()),2);
  if(a<0){
    return -1*a;
  }else{
    return a;
  }
}

void Segment::print(){
  this->a.print();
  this->b.print();
};

typedef struct{
  Point data[MAX_SOM];
  int n;
}Polygone;

Polygone* creeTriangle(Point* p1, Point* p2, Point* p3){
    Polygone* triangle = new Polygone();
    triangle->data[0]=*p1;
    triangle->data[1]=*p2;
    triangle->data[2]=*p3;
    triangle->n=3;
    return triangle;    
}

double perimetre(Polygone* p){
  Point a = p->data[0];
  Point b = p->data[1];
  Point c = p->data[2];
  Segment sa = {a.getX(),a.getY(),b.getX(),b.getY()};
  Segment sb = {b.getX(),b.getY(),c.getX(),c.getY()};
  Segment sc = {c.getX(),c.getY(),a.getX(),a.getY()};
  return sa.longeur()+sb.longeur()+sc.longeur();
}

void affiche(Polygone* p){
  p->data[0].print();
  p->data[1].print();
  p->data[2].print();
}

int main(){
  Point pt1 = {0,0};
  Point pt2 = {3,3};
  Point pt3 = {1.5,1.5};
  Polygone* p1 = creeTriangle(&pt1,&pt2,&pt2);
  Polygone p2 = *p1;
  affiche(p1);
  affiche(&p2);
  Polygone* tab = (Polygone*)malloc(2*sizeof(Polygone)); 
  tab[0]=p2;
  tab[1]=*p1;
  delete p1;
  delete tab;
  return 0;
}