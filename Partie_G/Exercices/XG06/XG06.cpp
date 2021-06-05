#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

bool isFract(string& s){
  int maxRecursion = s.length();
  int index = 0;
  int state = 1;
  int isDigit = 1;
  int isPoint = 0;
  do{
    isDigit = isdigit(s[index]);
    if(isDigit){
      if(state == 1){
        state = 2;
      }else if(state == 3){
        state = 4;
      }else if(state!=2 && state !=4){
        return false;
      }
    }else if(s[index] == '.'){
      isPoint = true;  
      if(state==2){
        state = 3;
      }else{
        return false;
      }
    }else{
      return false;
    }
    index+=1;
  }while((isDigit || isPoint) && index<maxRecursion);
  return state==4;
}

int main(){
  srand(time(NULL));
  string s1 = "33.5";
  string s2 = "33.5.5";
  string s3 = "abcedfrt";
  string s4 = ".5.5";
  string s5 = "5..5";
  string s6 = "466631587.51638463";
  cout << isFract(s1) << "\n" << isFract(s2) << "\n" << isFract(s3) << "\n" << isFract(s4) << "\n" << isFract(s5) << "\n" << isFract(s6) << "\n" << endl;
  return 0;
}