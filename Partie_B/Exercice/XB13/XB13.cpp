/*char b0 = ct&1;
return b<<7 | oct 1
*/


#include <stdio.h>

char rotD(char oct){
  printf("%d\n",oct);
  char b0 = oct&1;
  return oct>>1 |  b0<<7;  
}
int main(){
  printf("%d\n",rotD('b'));
  return 0;
}