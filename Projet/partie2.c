/*
  gcc Valentin_VERSTRACTE_partie1.cpp -g -Wall -o Valentin_VERSTRACTE_partie1
  commande pour compiler
  
  ./Valentin_VERSTRACTE_partie1 
  commande pour exécuter
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_COLONNES 15  // Longueur de la grille(nombre de colonnes)
#define NB_LIGNES 19    // Largeur de la grille(nombre de lignes)
#define AFF_VIDE '-'    // Caractère représentant les cases vides pour l’affichage
#define AFF_MUR  'X'    // Caractère représentant les murs pour l’affichage
#define AFF_BORD ' '    // Caractère représentant les bords pour l’affichage
#define PUSH_VALUE 2    // Valeur utiliser pour empiler un entier
#define DEBUG 1         // utiliser pour le debug

char* Grille = NULL;

/*
  retourne l'identifiant d'une case avec la ligne et colonne donnée en paramètre 
  * {int} ligne représente la ligne souhaiter
  * {int} colonne représente la colonne souhaiter
  * return {int}
*/
int getID(int ligne, int colonne)
{ 
  if(colonne>=NB_COLONNES || ligne >=NB_LIGNES)
  {
    printf("%s\n","Erreur, impossible d'avoir cette ID");
    return -1;
  } 
  return NB_COLONNES*ligne+colonne;
}

/*
  retourne la première coordonnée (ligne) d'une case dont on donne l'identifiant
  * {int} id 
*/
int getLigne(int id)
{
  return (int)(id/NB_COLONNES);
}


/*
  retourne la deuxième coordonnée (colonne) d'une case dont on donne l'identifiant
  * {int} id
  * return {int} 
*/
int getCol(int id)
{
  return id-getLigne(id)*NB_COLONNES;
}

/*
  place la valeur dans la case de coordonnées données en paramètre
  * {int} ligne
  * {int} colonne
  * {char} x
*/
void modifie(int ligne, int colonne, char x)
{
  int id = getID(ligne,colonne);
  Grille[id]=x;
}

/*
  retourne la valeur dans la case de coordonnées données en paramètre
  * {int} ligne
  * {int} colonne
  * return {int}
*/
char lit(int ligne, int colonne)
{
  int id = getID(ligne,colonne);
  return Grille[id];
}

/*
  affiche le Grille
*/
void affiche()
{
  for(int x=0;x<NB_COLONNES+2;x++)
  {
    printf("%c ",AFF_BORD);
  }
  printf("\n");
  for(int x=0;x<NB_LIGNES;x++)
  {
    printf("%c ",AFF_BORD);
    for(int y=0;y<NB_COLONNES;y++)
    {
      int id = getID(x,y);
      printf("%c ",Grille[id]);
    }
    printf("%c\n",AFF_BORD);
  }
  for(int x=0;x<NB_COLONNES+2;x++)
  {
    printf("%c ",AFF_BORD);
  }
  printf("\n");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
// Début de la partie 2
//-------------------------------------------------------------------------------------------------------------------------------------------------------

//int* Pile = NULL;
int* Pile=NULL;
int Sommet = 0;

/*
  empile un entier à la case id
  * {int} id 
*/
void push(int id)
{
  Pile[Sommet]=id;
  Sommet+=1;
}

int pop()
{
  Sommet-=1;
  int value = Pile[Sommet];
  return value;
}

void marque(int id)
{
  if(id>=0 && id<(NB_COLONNES*NB_LIGNES) && Grille[id]==AFF_VIDE)
  {
    push(id);
    Grille[id]=PUSH_VALUE;
  }
}

int connexe(){
  int casesBlanchesNb = 0;
  for(int id = 0;id<NB_COLONNES*NB_LIGNES;id++)
  {
    if(Grille[id]==AFF_VIDE)
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
      if (getLigne(id-1)==getLigne(id))
      {
        marque(id-1);
      }
      if (getLigne(id+1)==getLigne(id))
      {
        marque(id+1);
      }
      if (id-NB_COLONNES>=0) 
      {
        marque(id-NB_COLONNES);
      }
      if ((id+NB_COLONNES)<=NB_COLONNES*NB_LIGNES-1)
      {
        marque(id+NB_COLONNES);
      }
    }while(Sommet>=0);
    Sommet+=1;

    int casesBlanchesMarquerNb = 0;
    for (int x=0;x<NB_COLONNES*NB_LIGNES;x++)
    {
      if (Grille[x]==PUSH_VALUE)
      {
        casesBlanchesMarquerNb+=1;
        Grille[x] = AFF_VIDE;
      }
    }

    for(int x=0;x<NB_COLONNES*NB_LIGNES;x++){
      Pile[x]=0;
    }
    return casesBlanchesMarquerNb==casesBlanchesNb;
  }
}

// --------------------------------------------------------------------

/*
  retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
  une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthes
  * {int} 
*/
int* genRandomAlreadyConnexe=NULL;
int genGetRandomPosition()
{
  int shouldContinue = 1;
  int tosrand = time(NULL);
  int random = 0;
  int maxRecursion = NB_COLONNES*NB_LIGNES*100;
  int recursion = 0;
  do
  {
    recursion++;
    tosrand+=1;
    srand(tosrand);
    random = ((double) rand())/RAND_MAX*(NB_COLONNES*NB_LIGNES-2)+1;
    if(Grille[random]==AFF_VIDE && random!=0 && genRandomAlreadyConnexe[random]==0)
    {
      shouldContinue=0;
    }
  }while(shouldContinue && recursion<=maxRecursion);

  if(recursion>=maxRecursion)
  {
    if(DEBUG)
    {
      printf("%s\n","Erreur : limite de récursion pour la génération du labyrithne atteinte");
    }
    return -1;
  }

  return random;
}

void gen_lab(int k){
  if(k<(NB_COLONNES+NB_LIGNES-1))
  {
    printf("%s\n","Erreur : pas assez de cases blanches pour générer un labyrinthe intéressant");
  }else
  {
    for(int x=0;x<NB_LIGNES;x++)
    {
      for(int y=0;y<NB_COLONNES;y++)
      {
        int squareID = getID(x,y);
        Grille[squareID]=AFF_VIDE;
      } 
    }

    int wallToBuildRemaining = (NB_COLONNES*NB_COLONNES)-k;
    int canContinue = 1;
    do
    {
      int randomPositionID = genGetRandomPosition();
      canContinue = randomPositionID!=-1;
      if(canContinue){
        Grille[randomPositionID]=AFF_MUR;
        int connexeResult = connexe();
        if(connexeResult)
        {
          wallToBuildRemaining--;
          for(int x=0;x<NB_LIGNES;x++)
          {
            for(int y=0;y<NB_COLONNES;y++)
            {
              genRandomAlreadyConnexe[getID(x,y)]=0;
            }
          }
        }else
        {
          Grille[randomPositionID]=AFF_VIDE;
          genRandomAlreadyConnexe[randomPositionID]=1;
        }
      }
    }while(wallToBuildRemaining>0 && canContinue);
  }
}

int disMin(int id1, int id2)
{
  return 0;
}

int main()
{
  Grille = (char*)calloc((NB_LIGNES*NB_COLONNES),sizeof(char));
  Pile = (int*)calloc((NB_LIGNES*NB_COLONNES),sizeof(int)); 
  genRandomAlreadyConnexe = (int*)calloc((NB_LIGNES*NB_COLONNES),sizeof(int));
  gen_lab(33);
  affiche();
  free(Grille);
  free(Pile);
  free(genRandomAlreadyConnexe);
  return 0;
}