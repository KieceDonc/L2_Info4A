#include <stdio.h>

class Date{
  private:
    char j;
    char m;
    int a;

    public:
      Date();
      Date(int jour, int mois, int annee);
      void affiche();
      int getJ();
      int getM();
      int getA();
      void set(int jour, int mois, int annee);
};

Date::Date(){
  this->j = 1;
  this->m = 1;
  this->a = 1970;
}

Date::Date(int jour, int mois, int annee){
  this->j = jour;
  this->m = mois;
  this->a = annee;
}

void Date::affiche(){
  printf("%d/%d/%d",this->getA(),this->getM(),this->getA());
}

int Date::getJ(){
  return this->j;
}

int Date::getM(){
  return this->m;
}

int Date::getA(){
  return this->a;
}

void Date::set(int jour, int mois, int annee){
  this->a = annee;
  this->m = mois;
  this->j = jour;
}

class PileDates{
  private:
    Date* data;
    int n;
    int capa;

  public:
    PileDates(int capa);
    ~PileDates();
    PileDates(const PileDates& m);
    PileDates& operator=(const PileDates& m);
    void empile(Date d);
    Date depile();
};

PileDates::PileDates(int capa){
  this->capa = capa;
}

PileDates::~PileDates(){
  delete this->data;
}

PileDates::PileDates(const PileDates& m){
  this->n = m.n;
  this->capa = m.capa;
  this->data = new Date[m.capa];
  for(int x=0;x<m.n;x++){
    this->data[x] = m.data[x];
  }
}

PileDates& PileDates::operator=(const PileDates& m){
  delete this->data;
  this->data = new Date[m.capa];
  this->capa = m.capa;
  this->n = m.n;
  for(int x=0;x<this->n;x++){
    this->data[x] = m.data[x];
  }
  return *this;
}

void PileDates::empile(Date d){
  if(this->n<this->capa){
    this->data[n] = d; 
    this->n+=1;
  }
}

Date PileDates::depile(){
  if(this->n>0){
    this->n-=1;
    return this->data[n];
  }else{
    printf("Erreur depile");
  }
}