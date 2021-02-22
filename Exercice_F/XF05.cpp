#include <stdio.h>

class Date{

  private:
    char jour;
    char mois;
    int annee;

  public:
    Date(){
      this->jour='l';
      this->mois='m';
      this->annee=1900;
    }

    Date(char jour,char mois,int annee){
      this->jour = jour;
      this->mois = mois;
      this->annee = annee;
    }

    void setJour(char j){
      this->jour = j;
    }

    int compare(Date& d1, Date& d2){
      return d1.annee==d2.annee && d1.mois==d2.mois && d1.jour==d2.jour;
    }

    int compare(Date& autre){
      return this->annee==autre.annee && this->mois==autre.mois && this->jour==autre.jour;
    }
};

int main(){
  Date d1 = {'l','j',2000};
  Date d2 = {'l','j',2000};
  Date d3 = {'m','v',2020};
  printf("%d\n",d1.compare(d3));
  return 0;
}