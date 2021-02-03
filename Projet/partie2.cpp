/*
  gcc Valentin_VERSTRACTE_partie1.cpp -g -Wall -o Valentin_VERSTRACTE_partie1
  commande pour compiler
  
  ./Valentin_VERSTRACTE_partie1 
  commande pour exécuter
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_COLONNES 8 //Longueur de la grille(nombre de colonnes)
#define NB_LIGNES 8   //Largeur de la grille(nombre de lignes)
#define AFF_VIDE '-'  //Caractère représentant les cases vides pour l’affichage
#define AFF_MUR  'X'  //Caractère représentant les murs pour l’affichage
#define AFF_BORD 'M'  //Caractère représentant les bords pour l’affichage
#define POP_VALUE 0   // Valeur utiliser pour dépiler un entier
#define PUSH_VALUE 2  // Valeur utiliser pour empiler un entier
#define DEBUG 1       // utiliser pour le debug

char Grille[NB_COLONNES*NB_LIGNES] = {0};

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

int* Pile = new int[NB_COLONNES*NB_LIGNES];

/*
  empile un entier à la case id
  * {int} id 
*/
void push(int id)
{
  Pile[id]=PUSH_VALUE;
}

/*
  dépile un entier à la case id et le retourne
  * {int} id 
  * return {int} valeur de la case id dans la pile
*/
int pop(int id)
{
  int valeur = Pile[id];
  Pile[id] = POP_VALUE;
  return valeur;  
}

/*
  retourne l'id de la case au dessus de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getCaseSuperieurID(int id)
{
  int up_ID = id+NB_LIGNES;
  int oldColumn = getCol(id);
  int newColumn = getCol(up_ID);
  if(up_ID>(NB_LIGNES*NB_COLONNES-1) || oldColumn != newColumn)
  {
    return -1;
  }else{
    return up_ID;
  }
}

/*
  retourne l'id de la case en dessous de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getCaseInferieurID(int id)
{
  int down_ID = id-NB_LIGNES;
  int oldColumn = getCol(id);
  int newColumn = getCol(down_ID);
  if(down_ID<0 || oldColumn != newColumn)
  {
    return -1;
  }else{
    return down_ID;
  }
}

/*
  retourne l'id de la case à gauche de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getCaseGaucheID(int id)
{
  int left_ID = id-1;
  int newRow = getLigne(left_ID);
  int oldRow = getLigne(id);
  if(left_ID<0 || oldRow != newRow)
  {
    return -1;
  }else{
    return left_ID;
  }
}

/*
  retourne l'id de la case à droite de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getCaseDroiteID(int id)
{
  int right_ID = id+1;
  int newRow = getLigne(right_ID);
  int oldRow = getLigne(id);
  if(right_ID>(NB_LIGNES*NB_COLONNES-1) || oldRow != newRow)
  {
    return -1;
  }else{
    return right_ID;
  }
}

/*
  compte le nombre de cases blanches connectées entre elles à partir de la case id  
  * {int} id
  * return {int} 
*/
int nombreCasesBlanchesDetecter(int id)
{
  int square_up_id = getCaseSuperieurID(id);
  int square_down_id = getCaseInferieurID(id);
  int square_left_id = getCaseGaucheID(id);
  int square_right_id = getCaseDroiteID(id);  

  int whiteCount = 0;

  if(square_up_id!=-1)
  {
    int square_up_value = pop(square_up_id);
    if(square_up_value==PUSH_VALUE)
    {
      whiteCount++;
      whiteCount+=nombreCasesBlanchesDetecter(square_up_id);
    }
  }

  if(square_down_id!=-1)
  {
    int square_down_value = pop(square_down_id);
    if(square_down_value==PUSH_VALUE)
    {
      whiteCount++;
      whiteCount+=nombreCasesBlanchesDetecter(square_down_id);
    }
  }

  if(square_left_id!=-1)
  {
    int square_left_value = pop(square_left_id);
    if(square_left_value==PUSH_VALUE)
    {
      whiteCount++;
      whiteCount+=nombreCasesBlanchesDetecter(square_left_id);
    }
  }

  if(square_right_id!=-1)
  {
    int square_right_value = pop(square_right_id);
    if(square_right_value==PUSH_VALUE)
    {
      whiteCount++;
      whiteCount+=nombreCasesBlanchesDetecter(square_right_id);
    }
  }

  return whiteCount;
}

/*
  vérifie si toutes les cases blanches sont bien connectées entre elles
  * return {int} 1 si elles sont bien connéctées, 0 sinon
*/
int connexe()
{
  free(Pile);
  Pile = new int[NB_COLONNES*NB_LIGNES];
  int realWhiteSquareCount = 0;
  int randomSquareID=0;
  for(int x=0;x<NB_LIGNES;x++)
  {
    for(int y=0;y<NB_COLONNES;y++)
    {
      int id = getID(x,y);
      if(Grille[id] == AFF_VIDE)
      {
        push(id);
        realWhiteSquareCount++;
      }
    }
  }
  if(realWhiteSquareCount == 0)
  {
    printf("%s\n","Erreur : aucune case blanche");
    return 0;
  }else
  {
    int detectedWhiteSquareCount = nombreCasesBlanchesDetecter(randomSquareID);
    if(DEBUG)
    {
      printf("%s %d %s %d\n","Nombre de cases blanches détectées = ",detectedWhiteSquareCount,", Nombre de cases blanches réelles = ",realWhiteSquareCount);
    }
    return detectedWhiteSquareCount==realWhiteSquareCount;
  }
}

// --------------------------------------------------------------------

/*
  retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
  une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthes
  * {int} 
*/
int* genRandomAlreadyConnexe = new int[NB_COLONNES*NB_LIGNES];
int tosrand = 0;
int genGetRandomPosition()
{
  int shouldContinue = 1;
  int random = 0;
  do
  {
    tosrand+=1;
    srand(tosrand);
    random = ((double) rand())/RAND_MAX*(NB_COLONNES*NB_LIGNES-2)+1;
    if(Grille[random]==AFF_VIDE && random!=0 && genRandomAlreadyConnexe[random]==0)
    {
      shouldContinue=0;
      printf("%d\n",random);
    }
  }while(shouldContinue);
  return random;
}

void gen_lab(int k){
  if(k<(NB_COLONNES+NB_COLONNES-1))
  {
    printf("%s\n","Erreur : pas assez de cases blanches pour générer un labyrinthe intéressant");
  }else{
    // Première étape, on construit des murs partout sauf à l'entrée à et à la sortie
    for(int x=0;x<NB_LIGNES;x++)
    {
      for(int y=0;y<NB_COLONNES;y++)
      {
        int squareID = getID(x,y);
        Grille[squareID]=AFF_VIDE;
      } 
    }

    // L'algorithme est très loin d'être efficace car il compte sur l'aléatoire ( d'où la protection maxRecursion )
    // ici on ajoute des cases blanches aléatoirements
    int maxRecursion = NB_COLONNES*NB_LIGNES*100;
    int recursionCount = 0;
    int wallToBuildRemaining = (NB_COLONNES*NB_COLONNES)-k;
    do
    {
      int randomPositionID = genGetRandomPosition();
      Grille[randomPositionID]=AFF_MUR;
      int connexeResult = connexe();
      if(connexeResult)
      {
        wallToBuildRemaining--;
        free(genRandomAlreadyConnexe);
        genRandomAlreadyConnexe = new int[NB_COLONNES*NB_LIGNES];
      }else
      {
        Grille[randomPositionID]=AFF_VIDE;
        genRandomAlreadyConnexe[randomPositionID]=1;
      }
      recursionCount++;
    }while(wallToBuildRemaining>0&&recursionCount<=maxRecursion);
    
    if(recursionCount>=maxRecursion)
    {
      printf("%s\n","Erreur : limite de récursion pour la génération du labyrithne atteinte");
    }
  }
}

int main()
{
  for(int x=0;x<NB_LIGNES;x++)
  {
    for(int y=0;y<NB_COLONNES;y++)
    {
      int id = getID(x,y);
      Grille[id]=AFF_VIDE;
    }
  }
  modifie(1,1,AFF_MUR);
  modifie(1,2,AFF_MUR);
  affiche();


  free(Pile);
  free(genRandomAlreadyConnexe);
  return 0;
}