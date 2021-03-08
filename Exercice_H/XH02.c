#include <stdio.h>

typedef struct{
  double x;
  double y;
}Point;

typedef struct{
  Point* a;
  Point* b;
}Segment;

int main(){
  Point* t = (Point*)malloc(sizeof(Point));
  t->x = 1;
  t->y = 2;

  Point a = {1,2};
  Point b = {1,2};  
  Segment s = {&a,&b};
  
  free(t);
  return 0;
}