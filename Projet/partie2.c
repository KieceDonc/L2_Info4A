#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AFF_VIDE '-'    // Caractère représentant les cases vides pour l’affichage
#define AFF_MUR  'X'    // Caractère représentant les murs pour l’affichage
#define AFF_BORD ' '    // Caractère représentant les bords pour l’affichage
#define PUSH_VALUE 2    // Valeur utiliser pour empiler un entier
#define DEBUG 1         // utiliser pour le debug

int NB_COLONNES = 10; // Longueur de la grille(nombre de colonnes)
int NB_LIGNES = 10;   // Largeur de la grille(nombre de lignes)
char* Grille = NULL;
int robotAPosition = -1;
int robotBPosition = -1;

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
      if(id==robotAPosition)
      {
        printf("A ");
      }else if(id==robotBPosition)
      {
        printf("B ");
      }else
      {
        printf("%c ",Grille[id]);
      }
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

int getUpID(int id){
  if(id-NB_COLONNES>=0){
    return id-NB_COLONNES;
  }else{
    return -1;
  }
}

int getDownID(int id){
  if((id+NB_COLONNES)<=NB_COLONNES*NB_LIGNES-1){
    return id+NB_COLONNES;
  }else{
    return -1;
  }
}

int getLeftID(int id){
  if(getLigne(id-1)==getLigne(id)){
    return id-1;
  }else{
    return -1;
  }
}

int getRightID(int id){
  if(getLigne(id+1)==getLigne(id)){
    return id+1;
  }else{
    return -1;
  }
}

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
      int id_up = getUpID(id);
      int id_down = getDownID(id);
      int id_left = getLeftID(id);
      int id_right = getRightID(id);
      if(id_up!=-1){
        marque(id_up);
      }
      if(id_down!=-1){
        marque(id_down);
      }
      if(id_left!=-1){
        marque(id_left);
      }
      if(id_right!=-1){
        marque(id_right);
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
int genGetRandomPosition(int* genRandomAlreadyConnexe)
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

    int* genRandomAlreadyConnexe = (int*)calloc((NB_LIGNES*NB_COLONNES),sizeof(int)); // retiens les nombres aléatoires non connexe 
    int wallToBuildRemaining = (NB_COLONNES*NB_LIGNES)-k;
    int canContinue = 1;
    do
    {
      int randomPositionID = genGetRandomPosition(genRandomAlreadyConnexe);
      canContinue = randomPositionID!=-1;
      if(canContinue)
      {
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
    free(genRandomAlreadyConnexe);
  }
}

// https://stackoverflow.com/questions/8440816/warning-implicit-declaration-of-function
static void distMarque(int id,int value,int* distPile);
static void distMarqueVoisins(int id,int value,int* distPile);

/*
  Marque la distance de la case id par rapport à la première case passé en paramètre de distMarque
  et demande à marquer les cases voisines de id (crée un appel récursif qui va marquer toutes les 
  cases de la grille)
*/
void distMarque(int id,int value,int* distPile){
  int disPileValue = distPile[id];
  if(disPileValue==0){
    distPile[id]=value;
    distMarqueVoisins(id,value,distPile);
  }else if(value<disPileValue){
    distPile[id]=value;
    distMarqueVoisins(id,value,distPile);
  }
}

/*
  Vérifie si les cases voisines peuvent marquer la distance de la case id par rapport à la première 
  case passé en paramètre de distMarque, si oui les marques
*/
void distMarqueVoisins(int id,int value,int* distPile){
  int id_up = getUpID(id);
  int id_down = getDownID(id);
  int id_left = getLeftID(id);
  int id_right = getRightID(id);
  if(id_up!=-1 && Grille[id_up]!=AFF_MUR){
    distMarque(id_up,value+1,distPile);
  }
  if(id_down!=-1 && Grille[id_down]!=AFF_MUR){
    distMarque(id_down,value+1,distPile);
  }
  if(id_left!=-1 && Grille[id_left]!=AFF_MUR){
    distMarque(id_left,value+1,distPile);
  }
  if(id_right!=-1 && Grille[id_right]!=AFF_MUR){
    distMarque(id_right,value+1,distPile);   
  }
}

int distMin(int id_current, int id_dest){
  int* distPile = (int*)calloc((NB_LIGNES*NB_COLONNES),sizeof(int));
  distMarque(id_current,1,distPile);
  int minValue = distPile[id_dest];
  free(distPile);
  return minValue;
}

// l'idée est de calculer la plus grande distance au prochain "tour" entre le robot A et le robot B pour avoir le meilleur mouvement
int bestMoveRobotAStrat1(){
  int* dist = (int*)calloc((4),sizeof(int));
  for(int x=0;x<4;x++){
    dist[x]=NB_COLONNES*NB_LIGNES+50;
  }

  int id_up = getUpID(robotAPosition);
  int id_down = getDownID(robotAPosition);
  int id_left = getLeftID(robotAPosition);
  int id_right = getRightID(robotAPosition);
  
  if(id_up!=-1 && Grille[id_up]!=AFF_MUR){
    dist[0] = distMin(id_up,robotBPosition);
  }
  if(id_down!=-1 && Grille[id_down]!=AFF_MUR){
    dist[1] = distMin(id_down,robotBPosition);
  }
  if(id_left!=-1 && Grille[id_left]!=AFF_MUR){
    dist[2] = distMin(id_left,robotBPosition);
  }
  if(id_right!=-1 && Grille[id_right]!=AFF_MUR){
    dist[3] = distMin(id_right,robotBPosition);
  }

  int bestDistIndex = 4;
  int bestDist = distMin(robotAPosition,robotBPosition);
  for(int x=0;x<4;x++){
    if(dist[x]>bestDist){
      bestDistIndex = x;
      bestDist = dist[x];
    }
  }

  free(dist);
  
  switch(bestDistIndex){
    case 0 :{
      return id_up;
    };
    case 1:{
      return id_down;
    };
    case 2:{
      return id_left;
    }
    case 3:{
      return id_right;
    }
    case 4 :{
      return robotAPosition;
    }
  }
}

// l'idée est de calculer la plus petite distance au prochain "tour" entre le robot A et le robot B pour avoir le meilleur mouvement
int bestMoveRobotBStrat1(){
  int* dist = (int*)calloc((4),sizeof(int));
  for(int x=0;x<4;x++){
    dist[x]=NB_COLONNES*NB_LIGNES+50;
  }

  int id_up = getUpID(robotBPosition);
  int id_down = getDownID(robotBPosition);
  int id_left = getLeftID(robotBPosition);
  int id_right = getRightID(robotBPosition);
  
  if(id_up!=-1 && Grille[id_up]!=AFF_MUR){
    dist[0] = distMin(robotAPosition,id_up);
  }
  if(id_down!=-1 && Grille[id_down]!=AFF_MUR){
    dist[1] = distMin(robotAPosition,id_down);
  }
  if(id_left!=-1 && Grille[id_left]!=AFF_MUR){
    dist[2] = distMin(robotAPosition,id_left);
  }
  if(id_right!=-1 && Grille[id_right]!=AFF_MUR){
    dist[3] = distMin(robotAPosition,id_right);
  }

  int bestDistIndex = 4;
  int bestDist = distMin(robotBPosition,robotAPosition);
  for(int x=0;x<4;x++){
    if(dist[x]<bestDist){
      bestDistIndex = x;
      bestDist = dist[x];
    }
  }

  free(dist);
  
  switch(bestDistIndex){
    case 0 :{
      return id_up;
    };
    case 1:{
      return id_down;
    };
    case 2:{
      return id_left;
    }
    case 3:{
      return id_right;
    }
    case 4 :{
      return robotBPosition;
    }
  }
}

void simulationRobot(){
  int cmptSimulation = 0;
  robotAPosition=0;
  robotBPosition=NB_COLONNES*NB_LIGNES-1;
  affiche();

  do{
    cmptSimulation+=1;
    robotAPosition = bestMoveRobotAStrat1();
    robotBPosition = bestMoveRobotBStrat1();
    affiche();
  }while(robotAPosition!=robotBPosition && cmptSimulation<=NB_COLONNES*NB_LIGNES*100);

  if(robotAPosition == robotBPosition){
    printf("Le robot B a réussi à atteindre le robot A");
  }else{
    printf("Le robot B n'a pas réussi à atteindre le robot A");
  }
}

int main()
{
  Grille = (char*)calloc((NB_LIGNES*NB_COLONNES),sizeof(char));
  Pile = (int*)calloc((NB_LIGNES*NB_COLONNES),sizeof(int)); 
  gen_lab(30*2);
  affiche();
  simulationRobot();
  free(Grille);
  free(Pile);
  return 0;
}