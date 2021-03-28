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
  printf("%d/%d/%d\n",this->getA(),this->getM(),this->getA());
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
    void duplique(const PileDates& m);
};

PileDates::PileDates(int capa){
  this->capa = capa;
}

PileDates::~PileDates(){
  delete this->data;
}

PileDates::PileDates(const PileDates& m){
  duplique(m);
}

PileDates& PileDates::operator=(const PileDates& m){
  delete this->data;
  duplique(m);
  return *this;
}

void PileDates::empile(Date d){
  if(this->n<this->capa){
    Date* tmp = this->data;
    this->capa+=10;
    this->data = new Date[this->capa];
    for(int x=0;x<this->n;x++){
      this->data[x] = tmp[x];
    }
    delete tmp;
  }
  this->data[n] = d;
  this->n+=1;
}

Date PileDates::depile(){
  if(this->n>0){
    this->n-=1;
    return this->data[n];
  }else{
    printf("Erreur depile");
    return Date{};
  }
}

void PileDates::duplique(const PileDates& m){
  this->data = new Date[m.capa];
  this->capa = m.capa;
  this->n = m.n;
  for(int x=0;x<n;x++){
    this->data[x] = m.data[x];
  }
}

void testPileDates(){
  PileDates* p = new PileDates(4);
  p->empile(Date{26,3,2020});
  PileDates w = *p;
  Date d0 = p->depile();
  d0.affiche();
  Date d1 = w.depile();
  d1.affiche();
  delete p;
}

int main(){
  testPileDates();
  return 0;
}