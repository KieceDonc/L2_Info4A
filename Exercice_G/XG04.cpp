#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

string mdp(string& caract, int n){
  string toReturn = "";

  for(int x=0;x<n;x++){
    int random = ((double) rand())/RAND_MAX*(caract.length());
    toReturn+=caract[random];
  }
  return toReturn;
}

int main(){
  srand(time(NULL));
  string caract = "AZERTYUIOPMLKJHGFDSQWXCVBNazertyuiopmlkjhgfdsqwxcvbn,;:!123654789*/=)àç_è-('\"é&";
  string password = mdp(caract,400);
  cout << password << endl;
  caract = "AZ";
  password = mdp(caract,50);
  cout << password << endl;
  return 0;
}