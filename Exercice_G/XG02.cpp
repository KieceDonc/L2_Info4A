#include <stdio.h>
#include <string>
#include <iostream>


int main(){
  std::string s = "zdzde 54 5de 54 8e7ddzed 1";
  int numberCount = 0;
  for(int x=0;x<s.length();x++){
    if(std::isdigit(s[x])){
      numberCount+=1;
    }
  }
  printf("%d\n",numberCount);
 return 0; 
}