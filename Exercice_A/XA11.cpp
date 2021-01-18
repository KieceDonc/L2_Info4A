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

void test5(int a){
  a = 987654321;
}

void test6(){
  int x=0;
  test5(x);
  printf("%d\n",x);
}

int main(){
  test3();
  test4();
  test6();
  return 0;
}