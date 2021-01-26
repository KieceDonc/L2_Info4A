#include <stdio.h>
#include <cstring>

void test2(){
  char s[20] = "abcdef";
  printf("%s\n",s+3);
  strcat(s+2,"xyz");
  printf("%s\n",s);
  strcpy(s+strlen(s),"abc");
  printf("%s\n",s);
}

int main(){
  test2();
  return 0;
}