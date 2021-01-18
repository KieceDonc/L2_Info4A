#include <stdio.h>

void test1(){
  int a = 123456789;
  printf("%d\n",a);
}

void test2(){
  int x;
  printf("%d\n",x);
}

void test3(){
  test1();
  test2();
}

void test4(){
  test1();
  printf("Hello\n");
  test2();
}

int main(){
  test3();
  test4();
  return 0;
}