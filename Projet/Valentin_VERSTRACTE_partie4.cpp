/*
  g++ Valentin_VERSTRACTE_partie4.cpp -g -Wall -o Valentin_VERSTRACTE_partie4
  commande pour compiler
  
  ./Valentin_VERSTRACTE_partie4
  commande pour exécuter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

// Attend que duree (en secondes) se soit écoulée depuis le dernier appel.
void synchro(double duree)
{
  static clock_t jalon = clock();
  jalon = jalon + (clock_t)(duree * CLOCKS_PER_SEC);;
  while(clock()<jalon);
}

class Labyrinthe
{
private:
  int nb_lignes;
  int nb_colonnes;
  int taille;
  int sommet;
  int idRobotA;
  int idRobotB;
  int savesrand;

  char* grille;
  int* pile;
  std::string aff;
  
  // Retourne le caractère à afficher pour la valeur val.
  char getAff(char val);

  int getIntelligentRandomID(int* noConnexe, int recursion);
  // Retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
  // une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthe 
  void connexePush(int id); // Empile un entier à la case id
  int connexePop(int sommet); // Dépile un entier et le retourne
  void connexeMarque(int id); // Gère si une case doit être marqué

public:
  /// Constructeurs et destructeurs
  Labyrinthe(int nLignes, int nColonnes, double density);
  Labyrinthe(int nLignes, int nColonnes); //Crée un labyrinthe vide.
  Labyrinthe(char data[]) ; //Crée un labyrinthe à partir d'un descripteur.
  ~Labyrinthe(); //Détruit le labyrinthe courant.
  
  /// Méthodes d'accès
  int getID(int ligne, int colonne); //Retourne l'identifiant d'une cellule.
  int getLigne(int id); //Retourne la ligne de la cellule d'identifiant id.
  int getCol(int id); //Retourne la colonne de la cellule d'identifiant id.
  void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
  char lit(int ligne, int colonne); //Retourne la valeur de la cellule de coordonnées (i,j).
  
  /// Méthode d'accès supplémentaires
  int getNbLignes(); //Retourne le nombre de lignes de la grille.
  int getNbColonnes(); //Retourne le nombre de lignes de la grille.
  int lit(int id); //Retourne la valeur de la cellule id.
  void modifie(int id, char x); //Modifie la valeur de la cellule id.
  int getUpID(int id); // Retourne l'id de la case en haut de celle donné en paramètre, si l'id en haut n'existe pas retourne -1
  int getDownID(int id); // Retourne l'id de la case en bas de celle donné en paramètre, si l'id en bas n'existe pas retourne -1
  int getLeftID(int id); // Retourne l'id de la case à gauche de celle donné en paramètre, si l'id à gauche n'existe pas retourne -1
  int getRightID(int id); // Retourne l'id de la case à droite de celle donné en paramètre, si l'id à droite n'existe pas retourne -1

  /// Méthodes d'affichage
  // Initialise les caractères utilisés pour l'affichage. Si motif contient n caractères alors
  // motif[i] est affiché pour représenter une case de valeur i entre 0 et n-2.
  // Toute autre valeur provoque l'affichage du caractère motif[n-1].
  void setAff(const char* motifs);
  void affiche(); // Affiche le labyrinthe.
  void afficheDescr(); //Affiche le descripteur du labyrinthe courant.
  
  /// Méthode de haut niveau
  bool connexe(); //Vérifie si toutes les cellules de valeur 0 sont connectées.

  void genLaby(int nb); //Produit un labyrinthe aléatoire connexe avec nb cases blanches.
  void distMarque(int id,int value,int* distPile);
  // Marque la distance de la case id par rapport à la première case passé en paramètre de distMarque
  // et demande à marquer les cases voisines de id (crée un appel récursif qui va marquer toutes les 
  // cases de la grille
  void distMarqueVoisins(int id,int value,int* distPile);
  // Vérifie si les cases voisines peuvent marquer la distance de la case id par rapport à la première 
  // case passé en paramètre de distMarque, si oui les marques
  int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.

  int getIdRobotA() {return idRobotA;}
  int getIdRobotB() {return idRobotB;}    
  void setIdRobotA(int id) {idRobotA = id;}
  void setIdRobotB(int id) {idRobotB = id;}

  // Produit un identifiant aléatoire de case vide (PAS un mur)/
  int caseRandom();

  // Réalise un mouvemement du robot prédateur. La grille ne doit contenir que des cases 
  // vides et des murs.
  // L'attribut idRobotA est modifié. La grille n'est pas modifiée.
  // Retourne false si les robots sont en contact (dans ce cas A n'est pas déplacé),
  // et true si les robots n'étaient pas en contact avant le déplacement de A.
  // Au moins un algorithme de déplacement doit être implémenté. Les algorithmes
  // implémentés doivent être numéroté à partir de 1. Par exemple, si deux algorithmes sont
  // implémentés, ils sont numérotés 1 et 2. Le paramètre algo désigne l'algorithme à
  // utiliser. Si un seul algorithme est utilisé, sa valuer doit être 1.
  bool deplaceRobotA(int algo);
  
  // Réalise un mouvemement du robot proie. Mêmes convension que deplaceRobotB.
  bool deplaceRobotB(int algo);

  // Place les robots (identifiés par les valeurs 2 et 3) dans la grille. Efface l'écran.
  // Affiche la grille. Enlève les robots de lagrille (pour ne pas perturber distMin).
  void visualisation();

  // Lance une poursuite dans le labyrinthe courant. Si silent == true, aucun affichage n'est
  // réalisé, sinon il y a affichage de chaque étape.
  // Une étape = un mouvement de chaque robot. Si le nombre d'étape atteint timeout, la
  // valeur timeout+1 est retournée, sinon le nombre d'étape avant contact des robots est 
  // retourné. Si random == true, les position initiales des robots sont aléatoires, sinon ce 
  // sont les coins supérieur gauche et inféieur droit.
  // Les paramètres algoA et algoB indiquent le algorithmes utilisé pour les robots.
  int course(int timeout, bool silent, bool random, int algoA, int algoB);

  // Réalise nCourses courses et retourne la médiane des valeurs retournées par les
  // appels à la méthode courses. Le apramètres algoA et algoB donnent les algorithmes
  // à utiliser pour les robots A et B.
  int evalue(int nCourses, int timeOut, int algoA, int algoB);
};

// Retourne le caractère à afficher pour la valeur val.
char Labyrinthe::getAff(char val)
{
  int antiWarningA = val;
  int antiWarningB = aff.length();
  if(val<0 || antiWarningA>antiWarningB)
  {
    return aff[aff.length()-1];
  }
  else
  {
    return aff[val];
  }
}

// Crée un labyrinthe vide.
Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
  this->setAff(" XABM");
  this->nb_lignes = nLignes;
  this->nb_colonnes = nColonnes;
  this->idRobotA = getID(0,0);
  this->idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
  this->grille = new char[this->getNbLignes()*this->getNbColonnes()];
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      this->grille[id]=getAff(0);
    }
  }
  this->pile = new int[this->getNbLignes()*this->getNbColonnes()];
  this->sommet = 0;
}

Labyrinthe::Labyrinthe(int nLignes, int nColonnes, double density)
{
  this->setAff(" XABM");
  this->nb_lignes = nLignes;
  this->nb_colonnes = nColonnes;
  this->idRobotA = getID(0,0);
  this->idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
  this->grille = new char[this->getNbLignes()*this->getNbColonnes()];
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      this->grille[id]=getAff(0);
    }
  }
  this->pile = new int[this->getNbLignes()*this->getNbColonnes()];
  this->sommet = 0;
  genLaby((int)(density * getNbColonnes() * getNbLignes()));  
}


// Crée un labyrinthe à partir d'un descripteur.
Labyrinthe::Labyrinthe(char data[])
{

  this->setAff(" XABM");
  this->nb_lignes = data[0];
  this->nb_colonnes = data[1];
  this->idRobotA = getID(0,0);
  this->idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
  this->grille = new char[this->getNbLignes()*this->getNbColonnes()];
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      this->grille[id]=getAff(data[x+2]);
    }
  }
  this->pile = new int[this->getNbLignes()*this->getNbColonnes()];
  this->sommet = 0;
}

// Détruit le labyrinthe courant.
Labyrinthe::~Labyrinthe()
{
  delete[] this->grille;
  delete[] this->pile;
}

// Retourne l'identifiant d'une cellule.
int Labyrinthe::getID(int ligne, int colonne)
{
  if(colonne >= this->getNbColonnes() || ligne >= this->getNbLignes())
  {
    printf("%d %d %d %d\n",ligne,colonne,this->getNbColonnes(),this->getNbLignes());
    printf("%s\n","Erreur, impossible d'avoir cette ID");
    return -1;
  } 
  return this->getNbColonnes()*ligne+colonne;
}

// Retourne la ligne de la cellule d'identifiant id.
int Labyrinthe::getLigne(int id)
{
  return (int)(id/this->getNbColonnes());
}

// Retourne la colonne de la cellule d'identifiant id.
int Labyrinthe::getCol(int id)
{
  return id-this->getLigne(id)*this->getNbColonnes();
}

// Modifie la valeur d'une cellule.
void Labyrinthe::modifie(int ligne, int colonne, char x)
{
  int id = this->getID(ligne,colonne);
  this->grille[id]=x;
}

// Retourne la valeur de la cellule de coordonnées (i,j).
char Labyrinthe::lit(int ligne, int colonne)
{
  int id = this->getID(ligne,colonne);
  return this->grille[id];
}

// Retourne le nombre de lignes de la grille.
int Labyrinthe::getNbLignes()
{
  return this->nb_lignes;
}

// Retourne le nombre de lignes de la grille.
int Labyrinthe::getNbColonnes()
{
  return this->nb_colonnes;
}

// Retourne la valeur de la cellule id.
int Labyrinthe::lit(int id)
{
  return this->grille[id];
}

// Modifie la valeur de la cellule id.
void Labyrinthe::modifie(int id, char x)
{
  this->grille[id]=x;
}

// Initialise les caractères utilisés pour l'affichage. Si motif contient n caractères alors
// motif[i] est affiché pour représenter une case de valeur i entre 0 et n-2.
// Toute autre valeur provoque l'affichage du caractère motif[n-1].
void Labyrinthe::setAff(const char* motifs)
{
  this->aff = motifs;
}

// Retourne l'id de la case en haut de celle donné en paramètre, si l'id en haut n'existe pas retourne -1
int Labyrinthe::getUpID(int id)
{
  if(id-this->getNbColonnes()>=0)
  {
    return id-this->getNbColonnes();
  }
  else
  {
    return -1;
  }
}

// Retourne l'id de la case en bas de celle donné en paramètre, si l'id en bas n'existe pas retourne -1
int Labyrinthe::getDownID(int id)
{
  if((id+this->getNbColonnes())<=this->getNbColonnes()*this->getNbLignes()-1)
  {
    return id+this->getNbColonnes();
  }
  else
  {
    return -1;
  }
}

// Retourne l'id de la case à gauche de celle donné en paramètre, si l'id à gauche n'existe pas retourne -1
int Labyrinthe::getLeftID(int id)
{
  if(this->getLigne(id-1)==this->getLigne(id))
  {
    return id-1;
  }
  else
  {
    return -1;
  }
}

// Retourne l'id de la case à droite de celle donné en paramètre, si l'id à droite n'existe pas retourne -1
int Labyrinthe::getRightID(int id)
{
  if(this->getLigne(id+1)==this->getLigne(id))
  {
    return id+1;
  }
  else
  {
    return -1;
  }
}

// Affiche le labyrinthe.
void Labyrinthe::affiche()
{
  printf("\n");
  for(int x=0;x<this->getNbColonnes()+2;x++)
  {
    printf("%c ",this->getAff(-1));
  }
  printf("\n");
  for(int x=0;x<this->getNbLignes();x++)
  {
    printf("%c ",this->getAff(-1));

    for(int y=0;y<this->getNbColonnes();y++)
    {
      printf("%c ",this->getAff(this->lit(this->getID(x,y))));
    }

    printf("%c\n",this->getAff(-1));
  }
  for(int x=0;x<this->getNbColonnes()+2;x++)
  {
    printf("%c ",this->getAff(-1));
  }
  printf("\n");  
}

// Vérifie si toutes les cellules de valeur 0 sont connectées.
bool Labyrinthe::connexe()
{
  int casesBlanchesNb = 0;
  for(int id = 0;id<this->getNbColonnes()*this->getNbLignes();id++)
  {
    if(this->lit(id)==0)
    {
      casesBlanchesNb+=1;
    }
  } 
  this->connexePush(0);
  if(casesBlanchesNb == 0)
  {
    printf("%s\n","Erreur : aucune case blanche");
    return 0;
  }
  else
  {
    do
    {
      int id = this->connexePop(sommet);
      int id_up = this->getUpID(id);
      int id_down = this->getDownID(id);
      int id_left = this->getLeftID(id);
      int id_right = this->getRightID(id);
      if(id_up!=-1)
      {
        this->connexeMarque(id_up);
      }
      if(id_down!=-1)
      {
        this->connexeMarque(id_down);
      }
      if(id_left!=-1)
      {
        this->connexeMarque(id_left);
      }
      if(id_right!=-1)
      {
        this->connexeMarque(id_right);
      }
    }while(this->sommet>=0);
    this->sommet+=1;

    int casesBlanchesMarquerNb = 0;
    for (int x=0;x<this->getNbColonnes()*this->getNbLignes();x++)
    {
      if (this->lit(x)==60)
      {
        casesBlanchesMarquerNb+=1;
        this->modifie(x,0);
      }
    }

    for(int x=0;x<this->getNbColonnes()*this->getNbLignes();x++)
    {
      this->pile[x]=0;
    }
    return casesBlanchesMarquerNb==casesBlanchesNb;
  }
}

// Empile un entier à la case id
void Labyrinthe::connexePush(int id)
{
  this->pile[this->sommet]=id;
  this->sommet+=1;
}

// Dépile un entier et le retourne
int Labyrinthe::connexePop(int sommet)
{
  this->sommet-=1;
  int value = this->pile[this->sommet];
  return value;
}

// Gère si une case doit être marqué
void Labyrinthe::connexeMarque(int id)
{
  if(id>=0 && id<(this->getNbColonnes()*this->getNbLignes()) && this->lit(id)==0)
  {
    this->connexePush(id);
    this->modifie(id,60);
  }
}

// Retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
// une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthe 
int Labyrinthe::getIntelligentRandomID(int* noConnexe, int recursion)
{
  int avaibleIDLength = 0;
  
  for(int x=0;x<this->getNbLignes()*this->getNbColonnes();x++)
  {
    if(this->lit(x)==0 && noConnexe[x]==0)
    {
      avaibleIDLength+=1;
    }
  }

  int avaibleID[avaibleIDLength];
  int avaibleIDIndex = 0;
  for(int x=0;x<this->getNbLignes()*this->getNbColonnes();x++)
  {
    if(this->lit(x)==0 && noConnexe[x]==0)
    {
      avaibleID[avaibleIDIndex] = x;
      avaibleIDIndex+=1;
    }
  }

  if(avaibleIDLength==0)
  {
    return -1;
  }

  srand((unsigned)time(NULL)+recursion);
  int random = ((double) rand())/RAND_MAX*(avaibleIDLength-1)+1;

  int id = avaibleID[random];
  if(id>=0&&id<=this->getNbLignes()*this->getNbColonnes())
  {
    return id;
  }
  else
  {
    return -1;
  }
}

// Produit un labyrinthe aléatoire connexe avec nb cases blanches.
void Labyrinthe::genLaby(int nb)
{
  if(nb<(this->getNbLignes()+this->getNbColonnes()-1))
  {
    printf("%s\n","Erreur : pas assez de cases blanches pour générer un labyrinthe intéressant");
  }
  else
  {
    for(int x=0;x<this->getNbLignes();x++)
    {
      for(int y=0;y<this->getNbColonnes();y++)
      {
        this->modifie(x,y,0);
      } 
    }

    int noConnexe[this->getNbLignes()*this->getNbColonnes()]; 
    int wallToBuildRemaining = (this->getNbLignes()*this->getNbColonnes())-nb;
    int canContinue = 1;
    int recursion = 0;
    int maxRecursion = this->getNbLignes()*this->getNbColonnes()*4;
    do
    {
      recursion+=1;
      int randomPositionID = getIntelligentRandomID(noConnexe,recursion);
      canContinue = randomPositionID!=-1;
      if(canContinue)
      {
        this->modifie(this->getLigne(randomPositionID),this->getCol(randomPositionID),1);
        int connexeResult = connexe();
        if(connexeResult)
        {
          wallToBuildRemaining--;
        }
        else
        {
          this->modifie(this->getLigne(randomPositionID),this->getCol(randomPositionID),0);
          noConnexe[randomPositionID]=1;
        }
      }
      else
      {
        // certaines cases considérées comme non connexe peuvent être par la suite considérées comme connexe
        for(int x=0;x<this->getNbLignes()*this->getNbColonnes()-1;x++)
        {
          noConnexe[x]=0;
        }
      }
    }while(wallToBuildRemaining>0 && recursion<maxRecursion);
  }
}


// Marque la distance de la case id par rapport à la première case passé en paramètre de distMarque
// et demande à marquer les cases voisines de id (crée un appel récursif qui va marquer toutes les 
// cases de la grille
void Labyrinthe::distMarque(int id,int value,int* distPile)
{
  int disPileValue = distPile[id];
  if(disPileValue==0 || value<disPileValue)
  {
    distPile[id]=value;
    this->distMarqueVoisins(id,value,distPile);
  }
}


// Vérifie si les cases voisines peuvent marquer la distance de la case id par rapport à la première 
// case passé en paramètre de distMarque, si oui les marques
void Labyrinthe::distMarqueVoisins(int id,int value,int* distPile)
{
  int id_up = this->getUpID(id);
  int id_down = this->getDownID(id);
  int id_left = this->getLeftID(id);
  int id_right = this->getRightID(id);
  if(id_up!=-1 && this->lit(id_up)!=1)
  {
    this->distMarque(id_up,value+1,distPile);
  }
  if(id_down!=-1 && this->lit(id_down)!=1)
  {
    this->distMarque(id_down,value+1,distPile);
  }
  if(id_left!=-1 && this->lit(id_left)!=1)
  {
    this->distMarque(id_left,value+1,distPile);
  }
  if(id_right!=-1 && this->lit(id_right)!=1)
  {
    this->distMarque(id_right,value+1,distPile);   
  }
}

// Retourne la distance minimum entre les cases id1 et id2.
int Labyrinthe::distMin(int id1, int id2)
{
  int* distPile = new int[this->getNbLignes()*this->getNbColonnes()];
  for(int x=0;x<this->getNbLignes()*this->getNbColonnes();x++){
    distPile[x]=0;
  }
  distMarque(id1,1,distPile);
  int minValue = distPile[id2];
  delete[] distPile;
  return minValue-1;
}

///============================================================================
/// Vous devez compléter l'implémentation de cette classe qui hérite de
/// La classe Labyrinthe. Toutes les méthodes publiques de Labyrinthe sont
/// disponibles. Vous pouvez ajouter des attributs et des méthodes.
///============================================================================

// Méthode fournie par O. Bailleux
void Labyrinthe::visualisation()
{
  // Les robots sont placés dans la grille avant l'affichage
  modifie(getIdRobotA(),2);
  modifie(getIdRobotB(),3);

  system("clear");
  affiche();

  // Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
  // optimaux par la méthode distMin.
  modifie(getIdRobotA(),0);
  modifie(getIdRobotB(),0);
}

// Méthode fournie par O. Bailleux
int Labyrinthe::course(int timeout, bool silent, bool random, int algoA, int algoB)
{
  if(random)
  {// Course avec positions initiales des robots aléatoire
    idRobotB = caseRandom();
    idRobotA = caseRandom();
  }
  else
  {// Course avec départ dans les coins opposés.
    idRobotA = getID(0,0);
    idRobotB = getID(getNbLignes()-1, getNbColonnes()-1);
  }
  if(!silent){
    this->visualisation();
  }
  
  int nEtapes = 0;
  bool contact = false;

  // Arret quand les robots se touchent ou de nombre maxi d'étapes atteint
  while(!contact && nEtapes<timeout)
  {
    // On déplace le robot A
    contact = !deplaceRobotA(algoA);

    // On déplace le robot B sauf s'il est en contact avec A
    if (!contact) contact = !deplaceRobotB(algoB);

    nEtapes++;
    if(!silent) 
    {// Délai et affichage seulement si on est pas en mode silencieux
      synchro(0.1);
      visualisation();
    }
  }

  if(contact)
  {
    return nEtapes;
  }
  else
  {
    return timeout+1;
  }
}

// Méthode fournie par O. Bailleux
int Labyrinthe::evalue(int nCourses, int timeout, int algoA, int algoB)
{
  std::vector<int> tab;
  //int* tab = new int[nCourses]; // Tableau des scores

  for(int i=0; i<nCourses; i++)
  {// On lance une course et récupère le score
    cout << i << " / " << nCourses;
    int score = course(timeout, true, true, algoA, algoB);
    tab.push_back(score);
    cout << " --> " << score << endl;
  }

  // Tri du tableau de score pour calcul de la médiane.
  sort(tab.begin(), tab.end());
  return tab[nCourses/2];
}

///============================================================================
/// Méthodes à compléter. Vous pouvez ajouter les méthodes supplémentaires
/// pour simplifier votre programme et le rendre plus lisible.
///============================================================================

int Labyrinthe::caseRandom()
{
  //  A COMPLETER
  int shouldContinue = 1;
  if(this->savesrand!=0){
    this->savesrand+=13;    
  }else{  
    this->savesrand = time(NULL);
  }
  int random = 0;
  int maxRecursion = this->getNbColonnes()*this->getNbLignes()*10;
  int recursion = 0;
  do
  {
    recursion++;
    this->savesrand+=1;
    srand(this->savesrand);
    random = ((double) rand())/RAND_MAX*(this->getNbColonnes()*this->getNbLignes()-1);
    if(this->lit(random)==0)
    {
      shouldContinue=0;
    }
  }while(shouldContinue && recursion<=maxRecursion);

  return random;
}

// Méthode à compléter
bool Labyrinthe::deplaceRobotA(int algo)
{
  int id_up = this->getUpID(this->getIdRobotA());
  int id_down = this->getDownID(this->getIdRobotA());
  int id_left = this->getLeftID(this->getIdRobotA());
  int id_right = this->getRightID(this->getIdRobotA());

  if(algo==0)
  {
    int* dist = new int[4] {-1,-1,-1,-1};
    if(id_up!=-1 && this->lit(id_up)==0)
    {
      dist[0] = this->distMin(id_up,this->getIdRobotB());
    }

    if(id_down!=-1 && this->lit(id_down)==0)
    {
      dist[1] = this->distMin(id_down,this->getIdRobotB());
    }

    if(id_left!=-1 && this->lit(id_left)==0)
    {
      dist[2] = this->distMin(id_left,this->getIdRobotB());
    }
    
    if(id_right!=-1 && this->lit(id_right)==0)
    {
      dist[3] = this->distMin(id_right,this->getIdRobotB());
    }

    int availableDistLength = 0;
    int currentDist = this->distMin(this->getIdRobotA(),this->getIdRobotB());
    for(int x=0;x<4;x++)
    {
      if(dist[x]!=-1 && dist[x]<currentDist)
      {
        availableDistLength+=1;
      }else
      {
        dist[x]=-1;
      }
    }

    if(availableDistLength==0)
    {
      delete[] dist;
      return true;
    }
    else
    { 
      int* availableDist = new int[availableDistLength];
      int availableDistIndex = 0;

      if(dist[0]!=-1)
      {
        availableDist[availableDistIndex]=id_up;
        availableDistIndex+=1;
      }

      if(dist[1]!=-1)
      {
        availableDist[availableDistIndex]=id_down;
        availableDistIndex+=1;
      }

      if(dist[2]!=-1)
      {
        availableDist[availableDistIndex]=id_left;
        availableDistIndex+=1;
      }

      if(dist[3]!=-1)
      {
        availableDist[availableDistIndex]=id_right;
        availableDistIndex+=1;
      }

      int random = ((double) rand())/RAND_MAX*(availableDistLength);
      int newPosition = availableDist[random];

      delete[] dist;
      delete[] availableDist;

      if(newPosition!=this->getIdRobotB())
      {
        this->idRobotA=newPosition;
        return true;
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    bool correctInput = false;
    char input;
    do
    {
      printf("Veuillez choisir une direction ( z au dessus, q à gauche, s en dessous, d à gauche )\n");
      cin >> input;
      correctInput = input=='z' || input=='q' || input=='s' || input=='d';
      int newPosition = 0;
      if(correctInput)
      {
        switch(input)
        {
          case 'z':
          {
            correctInput = id_up!=-1 && this->lit(id_up)==0;
            newPosition = id_up;
            break;
          }
          case 'q':
          {
            correctInput = id_left !=-1 && this->lit(id_left)==0;
            newPosition = id_left;
            break;
          }
          case 's':
          {
            correctInput = id_down !=-1 && this->lit(id_down)==0;
            newPosition = id_down;
            break;
          }
          case 'd':
          {
            correctInput = id_right !=-1 && this->lit(id_right)==0;
            newPosition = id_right;
            break;
          }
        }

        if(!correctInput)
        {
          printf("Il y a un mur, veuillez choisir une case valide\n");
        }
        else
        {
          if(newPosition!=this->getIdRobotB())
          {
            this->idRobotA=newPosition;
            return true;
          }
          else
          {
            return false;
          }
        }
      }
      else
      {
        printf("%c n'est pas une touche valide\n",input);
      }
    }while(!correctInput);
    return false;
  }
}

bool Labyrinthe::deplaceRobotB(int algo)
{
  // A COMPLETER AVEC AU MOINS UN ALGORITHME DE POURSUITE PROIE
  int id_up = this->getUpID(this->getIdRobotB());
  int id_down = this->getDownID(this->getIdRobotB());
  int id_left = this->getLeftID(this->getIdRobotB());
  int id_right = this->getRightID(this->getIdRobotB());

  if(algo==0)
  {
    bool correctInput = false;
    char input;
    do
    {
      printf("Veuillez choisir une direction ( z au dessus, q à gauche, s en dessous, d à gauche )\n");
      cin >> input;
      correctInput = input=='z' || input=='q' || input=='s' || input=='d';
      int newPosition = 0;
      if(correctInput){
        switch(input){
          case 'z':
          {
            correctInput = id_up!=-1 && this->lit(id_up)==0;
            newPosition = id_up;
            break;
          }
          case 'q':
          {
            correctInput = id_left !=-1 && this->lit(id_left)==0;
            newPosition = id_left;
            break;
          }
          case 's':
          {
            correctInput = id_down !=-1 && this->lit(id_down)==0;
            newPosition = id_down;
            break;
          }
          case 'd':
          {
            correctInput = id_right !=-1 && this->lit(id_right)==0;
            newPosition = id_right;
            break;
          }
        }

        if(!correctInput)
        {
          printf("Il y a un mur, veuillez choisir une case valide\n");
        }
        else
        {
          if(newPosition!=this->getIdRobotA())
          {
            this->idRobotB=newPosition;
            return true;
          }
          else
          {
            return false;
          }
        }
      }
      else
      {
        printf("%c n'est pas une touche valide\n",input);
      }
    }while(!correctInput);

    return false;
  }
  else if(algo==1)
  {
    bool done = false;
    int recursion = 0;
    int maxRecursion = 25;
    int nextID = -1;
    do
    {
      srand(time(NULL)+recursion);
      int random = ((double) rand()/RAND_MAX)*4;
      recursion+=1;
      switch(random)
      {
        case 0:
          if(id_up!=-1 && this->lit(id_up)==0)
          {
              done = true;
              nextID = id_up;
          }
          break;
        case 1:
          if(id_down!=-1 && this->lit(id_down)==0)
          {
              done = true;
              nextID = id_down;
          }
          break;
        case 2:
          if(id_left!=-1 && this->lit(id_left)==0)
          {
              done = true;
              nextID = id_left;
          }
          break;
        case 3:
          if(id_right!=-1 && this->lit(id_right)==0)
          {
              done = true;
              nextID = id_right;
          }
          break;
      }
      if(done)
      {
        done = this->idRobotA!=nextID;
        if(!done)
        {
          return false;
        }
      }
    }while(done && recursion<maxRecursion);
    
    if(nextID!=-1)
    {
      this->idRobotB=nextID;
    }

    return true;

  }
  else
  {
    int* dist = new int[4] {-1,-1,-1,-1};

    if(id_up!=-1 && this->lit(id_up)==0)
    {
      dist[0] = this->distMin(id_up,this->getIdRobotA());
    }

    if(id_down!=-1 && this->lit(id_down)==0)
    {
      dist[1] = this->distMin(id_down,this->getIdRobotA());
    }

    if(id_left!=-1 && this->lit(id_left)==0)
    {
      dist[2] = this->distMin(id_left,this->getIdRobotA());
    }
    
    if(id_right!=-1 && this->lit(id_right)==0)
    {
      dist[3] = this->distMin(id_right,this->getIdRobotA());
    }

    int availableDistLength = 0;
    int currentDist = this->distMin(this->getIdRobotA(),this->getIdRobotB());
    for(int x=0;x<4;x++)
    {
      if(dist[x]!=-1 && dist[x]>currentDist)
      {
        availableDistLength+=1;
      }
      else
      {
        dist[x]=-1;
      }
    }

    if(availableDistLength==0)
    {
      delete[] dist;
      return true;
    }
    else
    { 
      int* availableDist = new int[availableDistLength];
      int availableDistIndex = 0;

      if(dist[0]!=-1)
      {
        availableDist[availableDistIndex]=id_up;
        availableDistIndex+=1;
      }

      if(dist[1]!=-1)
      {
        availableDist[availableDistIndex]=id_down;
        availableDistIndex+=1;
      }

      if(dist[2]!=-1)
      {
        availableDist[availableDistIndex]=id_left;
        availableDistIndex+=1;
      }

      if(dist[3]!=-1)
      {
        availableDist[availableDistIndex]=id_right;
        availableDistIndex+=1;
      }

      int random = ((double) rand())/RAND_MAX*(availableDistLength)-1;
      int newPosition = availableDist[random];

      delete[] dist;
      delete[] availableDist;

      if(newPosition!=this->getIdRobotA())
      {
        this->idRobotB=newPosition;
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

///============================================================================
/// Quelques descripteurs qui seront utilisés pour évaluer les algos de poursuite
///============================================================================

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.8
char descripteur1[] = 
{ 20, 30,
0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 
0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 
1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes sans murs
char descripteur2[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.9
char descripteur3[] = 
{ 20, 30,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

// Gille de 20 lignes et 30 colonnes densité de cases vides 0.7
char descripteur4[] =
{ 20, 30,
0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 
0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 
0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 
1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 
1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 
1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 
1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 
0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 
1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
};

///============================================================================
/// Exemple d'utilisation.
///============================================================================

void testPoursuite()
{
  int dureeMax = 300;
  Labyrinthe labyrinthe(30, 60, 0.9);

  int duree = labyrinthe.course(dureeMax, false, true, 0, 1);

  if(duree > dureeMax)
  {
    cout << "Echec apres " << dureeMax << " etapes" << endl;
  }
  else
  {
    cout << "Succes apres " << duree << " etapes" << endl;
  }
}

void testEval()
{
  Labyrinthe labyrinthe(descripteur2);

  int score = labyrinthe.evalue(50, 100, 0, 1);

  cout << "Mediane : " << score << endl;
}

void testEvalAlgo2()
{
  Labyrinthe labyrinthe(descripteur2);

  int score = labyrinthe.evalue(100, 100, 0, 2);

  cout << "Mediane : " << score << endl;
}

void testPoursuiteManualPredator()
{
  int dureeMax = 3000000;
  Labyrinthe labyrinthe(30, 60, 0.9);
  
  int duree = labyrinthe.course(dureeMax, false, true, 1, 2);

  if(duree > dureeMax)
  {
    cout << "Echec apres " << dureeMax << " etapes" << endl;
  }
  else
  {
    cout << "Succes apres " << duree << " etapes" << endl;
  }  
}

void testPoursuiteManuelFugitive()
{
  int dureeMax = 3000000;
  Labyrinthe labyrinthe(30, 60, 0.9);
  
  int duree = labyrinthe.course(dureeMax, false, true, 0, 0);

  if(duree > dureeMax)
  {
    cout << "Echec apres " << dureeMax << " etapes" << endl;
  }
  else
  {
    cout << "Succes apres " << duree << " etapes" << endl;
  }
}

int main(int argc, const char * argv[])
{
  srand((unsigned)time(NULL));
  testPoursuiteManuelFugitive();
  testPoursuiteManualPredator();
  testPoursuite();
  testEval();
  testEvalAlgo2();
  return 0;
}