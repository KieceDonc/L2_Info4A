#include <stdio.h>
#include <stdlib.h>

typedef struct{
  double x;
  double y;
}Point;

typedef struct{
  Point a;
  Point b;
}Segment;

Segment* creeSeg(double x1, double x2, double y1, double y2){
  Segment* seg = (Segment*)malloc(sizeof(Segment));
  
  seg->a.x = x1;
  seg->a.y = x2;
  seg->b.x = y1;
  seg->b.y = y2;

  return seg;
}

void print_point(Point p){
  printf("x = %f, y = %f\n",p.x,p.y);
}

int main(){
  Segment s = {{0.0,0.0},{2.0,2.0}};
  Segment* w = creeSeg(0,0,2,2);
  w->a.x = 5;
  s=*w;
  print_point(w->a);
  free(w);
  return 0;
}