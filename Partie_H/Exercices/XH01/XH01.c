#include <stdio.h>

typedef struct{
  double x;
  double y;
}Point;

typedef struct{
  Point* a;
  Point* b;
}Segment;

void print_point(Point* p){
  printf("x = %f, y = %f\n",p->x,p->y);
}

void print_segment(Segment* s){
  print_point(s->a);
  print_point(s->b);
}

int main(){
  Point p1 = {5.0,7.2};
  Point p2 = {8,2.11};
  Segment s = {&p1,&p2};
  print_segment(&s);
  return 0;
}