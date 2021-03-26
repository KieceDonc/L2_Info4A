#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

string pgpc(string& s1, string& s2){
  
  string toReturn = "";
  int maxRecursion = s1.length() > s2.length() ? s1.length():s2.length();
  int shouldContinue = 1;
  int index = 0;
  do{
    shouldContinue = s1[index] == s2[index];
    if(shouldContinue){
      toReturn+=s1[index];
    }
    index+=1;
  }while(shouldContinue && index<maxRecursion);
  return toReturn;
}
int main(){
  string s1 = "abcedf";
  string s2 = "abcfge";
  string result = pgpc(s1,s2);
  cout << result << endl;
  return 0;
}