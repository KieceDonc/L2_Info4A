#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

bool similar(string& s1, string& s2){

  int distLength = s1.length()-s2.length();
  if(distLength>1 || distLength<-1){
    return false;
  }
  int index = 0;
  int differenceCount = 0;
  do{
    if(s1[index]!=s2[index]){
      differenceCount+=1;
    }
    index+=1;
  }while(differenceCount<2 && index<s1.length() && index<s2.length());
  return differenceCount<2;
}

int main(){
  srand(time(NULL));
  string s1 = "abcedf";
  string s2 = "abced";
  string s3 = "abcedfrt";
  cout << similar(s1,s2) << "\n" << similar(s1,s3) << endl;
  return 0;
}