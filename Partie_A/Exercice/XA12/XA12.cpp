#include <stdio.h>
#include <math.h>

int code(int j, int m, int a){
  return a*pow(10,4)+m*pow(10,2)+j;
}

int annee(int code){
  return code/pow(10,4);
}

int mois(int code){
  return (code - annee(code)*pow(10,4))/pow(10,2);
}

int jour (int code){
  return code-annee(code)*pow(10,4)-mois(code)*pow(10,2);
}

int compare(int date1,int date2){
  // false = 0, true = 1;
  // on veut retourner 0 quand date1 == date2
  // cqfd :
  return (!(date1==date2));
}

int main(){
  int date = code(1,1,2021);
  int date_test = code(1,1,2021);
  int result = compare(date,date_test);
  int date_year = annee(date);
  int date_month = mois(date);
  int date_day = jour(date);
  printf("%d\n",date);
  printf("%d\n",date_year);
  printf("%d\n",date_month);
  printf("%d\n",date_day);
  printf("%d\n",result);
  return 0;
}