#include <stdio.h>

/*
Déclarez une classe Date avec un attribut jour de type char, un attribut mois
de type char et un attribut annee de type int. Les attributs doivent être privés
(private).

Ajoutez à cette classe :

- un constructeur qui n'accepte aucun paramètre (un tel constructeur est appelé
constructeur par défaut) créant une instance de Date correspondant au 1/1/1900,

- une méthode setJour qui ne retrourne rien, accepte un paramètre j de type
char, et assigne à l’attribut jour la valeur de j.
*/

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

    void setJour(char j){
      this->jour = j;
    }
};

int main(){
  return 0;
}