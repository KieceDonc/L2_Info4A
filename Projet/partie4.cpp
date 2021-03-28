#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>


class Labyrinthe
{
private:
  int nb_lignes;
  int nb_colonnes;
  int taille;
  char* grille;
  std::string aff;
  
  // Retourne le caractère à afficher pour la valeur val.
  char getAff(char val);

public:
  /// Constructeurs et destructeurs
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
  int getIntelligentRandomID(int* noConnexe, int recursion);
  // Retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
  // une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthe 
  void genLaby(int nb); //Produit un labyrinthe aléatoire connexe avec nb cases blanches.
  void distMarque(int id,int value,int* distPile);
  // Marque la distance de la case id par rapport à la première case passé en paramètre de distMarque
  // et demande à marquer les cases voisines de id (crée un appel récursif qui va marquer toutes les 
  // cases de la grille
  void distMarqueVoisins(int id,int value,int* distPile);
  // Vérifie si les cases voisines peuvent marquer la distance de la case id par rapport à la première 
  // case passé en paramètre de distMarque, si oui les marques
  int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.
  
  /// Méthodes de démonstration
  // Matérialise un chemin de longueur minimale entre les cases d'identifiants
  // id1 et id2 en plaçant des valeurs 2 dans les cases de ce chemin.
  void chemin(int id1, int id2);
  // Lance une démonstration de productions de labyrinthes et de recherche de
  // chemins de longueur minimale.
  static void demo();
};

// Retourne le caractère à afficher pour la valeur val.
char Labyrinthe::getAff(char val)
{
  if(val<0 || val>aff.length()){
    return aff[aff.length()-1];
  }else{
    return aff[val];
  }
}

// Crée un labyrinthe vide.
Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
  this->nb_lignes = nLignes;
  this->nb_colonnes = nColonnes;
  this->grille = (char*)calloc(this->getNbLignes()*this->getNbColonnes(),sizeof(char));
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      this->grille[id]=getAff(0);
    }
  }
}

// Crée un labyrinthe à partir d'un descripteur.
Labyrinthe::Labyrinthe(char data[])
{
  this->nb_lignes = data[0];
  this->nb_colonnes = data[1];
  this->grille = (char*)calloc(this->getNbLignes()*this->getNbColonnes(),sizeof(char));
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      this->grille[id]=getAff(data[x+2]);
    }
  }
}

// Détruit le labyrinthe courant.
Labyrinthe::~Labyrinthe()
{
  delete this->grille;
}

// Retourne l'identifiant d'une cellule.
int Labyrinthe::getID(int ligne, int colonne)
{
  if(colonne >= this->getNbColonnes() || ligne >= this->getNbLignes())
  {
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
  }else
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
  }else
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
  }else
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
  }else
  {
    return -1;
  }
}

// Affiche le labyrinthe.
void Labyrinthe::affiche()
{
  printf("\n");
  for(int x=0;x<this->getNbLignes();x++)
  {
    for(int y=0;y<this->getNbColonnes();y++)
    {
      int id = getID(x,y);
      printf("%c ",this->getAff(this->lit(this->getID(x,y))));
    }
    
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
  marque(0);
  if(casesBlanchesNb == 0)
  {
    printf("%s\n","Erreur : aucune case blanche");
    return 0;
  }else
  {
    do
    {
      int id = pop();
      int id_up = getUpID(id);
      int id_down = getDownID(id);
      int id_left = getLeftID(id);
      int id_right = getRightID(id);
      if(id_up!=-1)
      {
        marque(id_up);
      }
      if(id_down!=-1)
      {
        marque(id_down);
      }
      if(id_left!=-1)
      {
        marque(id_left);
      }
      if(id_right!=-1)
      {
        marque(id_right);
      }
    }while(Sommet>=0);
    Sommet+=1;

    int casesBlanchesMarquerNb = 0;
    for (int x=0;x<this->getNbColonnes()*this->getNbLignes();x++)
    {
      if (Grille[x]==PUSH_VALUE)
      {
        casesBlanchesMarquerNb+=1;
        Grille[x] = 0;
      }
    }

    for(int x=0;x<this->getNbColonnes()*this->getNbLignes();x++)
    {
      Pile[x]=0;
    }
    return casesBlanchesMarquerNb==casesBlanchesNb;
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
  }else
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
  }else
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
        }else
        {
          this->modifie(this->getLigne(randomPositionID),this->getCol(randomPositionID),0);
          noConnexe[randomPositionID]=1;
        }
      }else
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
void Labyrinthe::distMarque(int id,int value,int* distPile){
  int disPileValue = distPile[id];
  if(disPileValue==0){
    distPile[id]=value;
    this->distMarqueVoisins(id,value,distPile);
  }else if(value<disPileValue){
    distPile[id]=value;
    this->distMarqueVoisins(id,value,distPile);
  }
}


// Vérifie si les cases voisines peuvent marquer la distance de la case id par rapport à la première 
// case passé en paramètre de distMarque, si oui les marques
void Labyrinthe::distMarqueVoisins(int id,int value,int* distPile){
  int id_up = this->getUpID(id);
  int id_down = this->getDownID(id);
  int id_left = this->getLeftID(id);
  int id_right = this->getRightID(id);
  if(id_up!=-1 && this->lit(id_up)!=1){
    this->distMarque(id_up,value+1,distPile);
  }
  if(id_down!=-1 && this->lit(id_down)!=1){
    this->distMarque(id_down,value+1,distPile);
  }
  if(id_left!=-1 && this->lit(id_left)!=1){
    this->distMarque(id_left,value+1,distPile);
  }
  if(id_right!=-1 && this->lit(id_right)!=1){
    this->distMarque(id_right,value+1,distPile);   
  }
}

// Retourne la distance minimum entre les cases id1 et id2.
int Labyrinthe::distMin(int id1, int id2)
{
  int* distPile = (int*)calloc((this->getNbLignes()*this->getNbColonnes()),sizeof(int));
  distMarque(id1,1,distPile);
  int minValue = distPile[id2];
  delete distPile;
  return minValue;
}