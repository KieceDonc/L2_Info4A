#include <stdlib.h>
#include <string>
#include <iostream>

int main(){

  std::string stringArray[] = {"abc","def","fgh","ijk"};
  for(int x=0;x<5;x++){
    int random0 = ((double) rand())/RAND_MAX*4;
    srand(x);
    int random1 = ((double) rand())/RAND_MAX*4;
    std::string toSave = stringArray[random0];
    stringArray[random0] = stringArray[random1];
    stringArray[random1] = toSave;
  }

  std::string result =  stringArray[0] + stringArray[1] + stringArray[2] + stringArray[3];
  std::cout << result << std::endl;
  return 0;
}