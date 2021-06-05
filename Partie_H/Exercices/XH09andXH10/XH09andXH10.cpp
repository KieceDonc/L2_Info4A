#include <stdio.h>

#define TPILE 5

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

    void print();
};

Segment::Segment() : a(0,0),b(0,0){

};

Segment::Segment(double x1,double y1,double x2,double y2) : a(x1,y1),b(x2,y2){

};

void Segment::print(){
  this->a.print();
  this->b.print();
};

typedef struct{
  Point data[TPILE];
  int top;
}PilePoints;

PilePoints* creePilePoints(){
  PilePoints* pilePoints = new PilePoints();
  pilePoints->top=0;
  return pilePoints;
}

void empile(PilePoints* p, Point* w){
  p->data[p->top]=*w;
  p->top+=1;
}

Point depile(PilePoints* p){
  Point pt = p->data[p->top];
  p->top-=1;
  return pt;
}

int main(){
  PilePoints* p1 = creePilePoints();
  Point* pt1 = new Point(0,0);
  Point* pt2 = new Point(2,2);
  empile(p1,pt1);
  empile(p1,pt2);
  PilePoints* p2 = p1;
  Point pt3 = depile(p2);
  pt3.print();
  PilePoints* p3 = p2;
  Point pt4 = depile(p3);
  pt4.print();
  delete p1;
  delete pt1;
  delete pt2;
  return 0;
}