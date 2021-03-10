#include <stdio.h>

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
    Segment(double x1,double y1,double x2,double y2);

    Segment();

    Point milieu();

    void print();
};

Segment::Segment(double x1,double y1,double x2,double y2) : a(x1,y1),b(x2,y2){
  
};

void Segment::print(){
  this->a.print();
  this->b.print();
}

int main(){
  Segment* s = new Segment(0,0,3.5,3.5);
  s->print();
  delete s;
  return 0;
}