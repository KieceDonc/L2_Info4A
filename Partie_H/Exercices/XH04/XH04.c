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

void print_point(Point* p){
  printf("x = %f, y = %f\n",p->x,p->y);
}

void print_segment(Segment* s){
  print_point(&s->a);
  print_point(&s->b);
}

int main(){  
  Segment s = {{0.0,0.0},{2.0,2.0}};
  Segment tab0[2]; 
  tab0[0] = s;
  tab0[1] = s;
  print_segment(&tab0[0]);
  print_segment(&tab0[1]);
  Segment* tab1 = (Segment*)malloc(2*sizeof(Segment));
  tab1[0] = tab0[0];
  tab1[1] = tab0[1];
  print_segment(&tab1[0]);
  print_segment(&tab1[1]);
  free(tab1);
  return 0;
}