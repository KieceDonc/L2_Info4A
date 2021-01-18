#include <stdio.h>

int analyse(){
  char c = getchar();
  int state = 1;
  while(1){
    switch (state){
      case 1:
        switch (c){
          case 'A':
            state = 2;
            break;
          default:
            return 0;
            break;
        }
        break;
      case 2:
        switch (c){
          case 'B':
            state = 3;
            break;
          case 'C':
            return 1;
            break;
          default:
            return 0;
            break;
        }
        break;
      case 3:
        switch (c){
          case 'C':
            return 1;
            break;
          default:
            return 0;
            break;
        }
        break;
      default:
        return 0;
        break;
    }
    c = getchar();
    c = getchar();
  }
}

int main(){
  printf("%d",analyse());
  return 0;
}