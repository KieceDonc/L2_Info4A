#include <stdio.h>
#include <cstring>

void presentation(){
  char s[10] = "abcdef";
  char t[] = "xxx";
  strcpy(s,t);
  printf("%s\n",s);
  printf("%c\n",s[4]);
  strcat(s,t);
  printf("%s -> %ld\n",s,strlen(s));
}

int main(){
  presentation();
  return 0;
}