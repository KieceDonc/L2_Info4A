#include <stdio.h>

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

    Point barycentre(Point pt2){
      double Ptx = this->x + pt2.x;
      double Pty=this->y + pt2.y;
      return Point(Ptx,Pty);
    };

    void print(){
      printf("%f %f",this->x,this->y);
    };
};


class SegmentR{
  private:
    Point* a;
    Point* b;

  public: 
    SegmentR(double x1, double y1, double x2, double y2);
    ~SegmentR();
    Point milieu();
    void print();
};

SegmentR::SegmentR(double x1, double y1, double x2, double y2){
  this->a = new Point(x1,y1);
  this->b = new Point(x2,y2);
}

SegmentR::~SegmentR(){
  delete this->a;
  delete this->b;
}

Point SegmentR::milieu(){
  return this->a->barycentre(*this->b);
}

void SegmentR::print(){
  printf("Point a = ");
  this->a->print();
  printf("\nPoint b = ");
  this->b->print();
  printf("\n");
}

int main(){
  SegmentR segment = {1,1,2,2};
  segment.print();
  return 0;
}