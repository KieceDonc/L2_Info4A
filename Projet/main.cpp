#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COLUMN 8  // Longeur de la grille (nombre de colonnes)
#define MAX_ROW 8     // Largeur de la grille (nombre de lignes)
#define AFF_VIDE '-'  // Caractère représentant les cases vides pour l’affichage
#define AFF_MUR 'X'   // Caractère représentant les murs pour l’affichage
#define AFF_BORD ' '  // Caractère représentant les bords pour l’affichage
#define POP_VALUE 0   // Valeur utiliser pour dépiler un entier
#define PUSH_VALUE 2  // Valeur utiliser pour empiler un entier
#define DEBUG 1       // utiliser pour le debug

char labyrinth[MAX_COLUMN*MAX_ROW] = {};

/*
  retourne l'identifiant d'une case avec la ligne et colonne donnée en paramètre 
  * {int} row représente la ligne souhaiter
  * {int} column représente la colonne souhaiter
  * return {int}
*/
int getID(int row, int column){ 
  if(column>=MAX_COLUMN || row >=MAX_ROW){
    printf("%s\n","Erreur, impossible d'avoir cette ID");
  } 
  return MAX_COLUMN*row+column;
}

/*
  retourne la première coordonnée (ligne) d'une case dont on donne l'identifiant
  * {int} id 
*/
int getRow(int id){
  return (int)(id/MAX_COLUMN);
}


/*
  retourne la deuxième coordonnée (colonne) d'une case dont on donne l'identifiant
  * {int} id
  * return {int} 
*/
int getColumn(int id){
  return id-getRow(id)*MAX_COLUMN;
}

/*
  place la valeur dans la case de coordonnées données en paramètre
  * {int} row
  * {int} column
  * {int} value
*/
void modify(int row, int column, char value){
  int id = getID(row,column);
  labyrinth[id]=value;
}

/*
  retourne la valeur dans la case de coordonnées données en paramètre
  * {int} row
  * {int} column
  * return {int}
*/
char read(int row, int column){
  int id = getID(row,column);
  return labyrinth[id];
}

/*
  affiche le labyrinthe
*/
void affiche(){
  for(int x=0;x<MAX_ROW;x++){
    for(int y=0;y<MAX_COLUMN;y++){
      int id = getID(x,y);
      printf("%c ",labyrinth[id]);
    }
    printf("\n");
  }
}

// ---------------------------------------------------------------------

int pile[MAX_COLUMN*MAX_ROW]= {};

/*
  empile un entier à la case id
  * {int} id 
*/
void push(int id){
  pile[id]=PUSH_VALUE;
}

/*
  dépile un entier à la case id et le retourne
  * {int} id 
  * return {int} valeur de la case id dans la pile
*/
int pop(int id){
  int value = pile[id];
  pile[id] = POP_VALUE;
  return value;  
}

/*
  retourne l'id de la case au dessus de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getUpSquareID(int id){
  int up_ID = id+MAX_ROW;
  int oldColumn = getColumn(id);
  int newColumn = getColumn(up_ID);
  if(up_ID>(MAX_ROW*MAX_COLUMN-1) || oldColumn != newColumn){
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
int getDownSquareID(int id){
  int down_ID = id-MAX_ROW;
  int oldColumn = getColumn(id);
  int newColumn = getColumn(down_ID);
  if(down_ID<0 || oldColumn != newColumn){
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
int getLeftSquareID(int id){
  int left_ID = id-1;
  int newRow = getRow(left_ID);
  int oldRow = getRow(id);
  if(left_ID<0 || oldRow != newRow){
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
int getRightSquareID(int id){
  int right_ID = id+1;
  int newRow = getRow(right_ID);
  int oldRow = getRow(id);
  if(right_ID>(MAX_ROW*MAX_COLUMN-1) || oldRow != newRow){
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
int detectedWhiteSquareCount(int id){
  int square_up_id = getUpSquareID(id);
  int square_down_id = getDownSquareID(id);
  int square_left_id = getLeftSquareID(id);
  int square_right_id = getRightSquareID(id);  

  int whiteCount = 0;

  /*if(id!=-1){
    int square_id_value = pop(id);
    if(square_id_value==PUSH_VALUE){
      whiteCount++;
      whiteCount+=detectedWhiteSquareCount(square_up_id);
    }
  }*/

  if(square_up_id!=-1){
    int square_up_value = pop(square_up_id);
    if(square_up_value==PUSH_VALUE){
      whiteCount++;
      whiteCount+=detectedWhiteSquareCount(square_up_id);
    }
  }

  if(square_down_id!=-1){
    int square_down_value = pop(square_down_id);
    if(square_down_value==PUSH_VALUE){
      whiteCount++;
      whiteCount+=detectedWhiteSquareCount(square_down_id);
    }
  }

  if(square_left_id!=-1){
    int square_left_value = pop(square_left_id);
    if(square_left_value==PUSH_VALUE){
      whiteCount++;
      whiteCount+=detectedWhiteSquareCount(square_left_id);
    }
  }

  if(square_right_id!=-1){
    int square_right_value = pop(square_right_id);
    if(square_right_value==PUSH_VALUE){
      whiteCount++;
      whiteCount+=detectedWhiteSquareCount(square_right_id);
    }
  }

  return whiteCount;
}

/*
  vérifie si toutes les cases blanches sont bien connectées entre elles
  * return {int} 1 si elles sont bien connéctées, 0 sinon
*/
int connexe(){
  pile[MAX_COLUMN*MAX_ROW]= {};
  int realWhiteSquareCount = 0;
  int randomSquareID=0;
  for(int x=0;x<MAX_ROW;x++){
    for(int y=0;y<MAX_COLUMN;y++){
      int id = getID(x,y);
      if(labyrinth[id] == AFF_VIDE){
        push(id);
        realWhiteSquareCount++;
      }
    }
  }
  if(realWhiteSquareCount == 0){
    printf("%s\n","Erreur : aucune case blanche");
    return 0;
  }else{
    int detectedWhiteSquareCountValue = detectedWhiteSquareCount(randomSquareID);
    if(DEBUG){
      printf("%s %d %s %d\n","Nombre de cases blanches détectées = ",detectedWhiteSquareCountValue,", Nombre de cases blanches réelles = ",realWhiteSquareCount);
      }
    return detectedWhiteSquareCountValue==realWhiteSquareCount;
  }
}

// --------------------------------------------------------------------

/*
  retourne une position aléatoire qui n'est pas une case blanche et qui contient au moins
  une case au dessus / en dessous / à gauche / à droite pour la génération du labyrinthes
  * {int} 
*/
int genRandomAlreadyConnexe[MAX_COLUMN*MAX_ROW] = {};
int genGetRandomPosition(){
  int shouldContinue = 1;
  int random = 0;
  int tosrand = time(NULL);
  do{
    tosrand+=1;
    srand(tosrand);
    random = ((double) rand())/RAND_MAX*(MAX_COLUMN*MAX_ROW-2)+1;
    if(labyrinth[random]==AFF_VIDE && random!=0 && genRandomAlreadyConnexe[random]==0){
      shouldContinue=0;
    }
  }while(shouldContinue);
  return random;
}

void gen_lab(int k){
  if(k<(MAX_COLUMN+MAX_COLUMN-1)){
    printf("%s\n","Erreur : pas assez de cases blanches pour générer un labyrinthe intéressant");
  }else{
    // Première étape, on construit des murs partout sauf à l'entrée à et à la sortie
    for(int x=0;x<MAX_ROW;x++){
      for(int y=0;y<MAX_COLUMN;y++){
        int squareID = getID(x,y);
        labyrinth[squareID]=AFF_VIDE;
      } 
    }

    // L'algorithme est très loin d'être efficace car il compte sur l'aléatoire ( d'où la protection maxRecursion )
    // ici on ajoute des cases blanches aléatoirements
    int maxRecursion = MAX_COLUMN*MAX_ROW*100;
    int recursionCount = 0;
    int wallToBuildRemaining = (MAX_COLUMN*MAX_COLUMN)-k;
    do{
      int randomPositionID = genGetRandomPosition();
      labyrinth[randomPositionID]=AFF_MUR;
      if(connexe()){
        wallToBuildRemaining--;
        genRandomAlreadyConnexe[MAX_COLUMN*MAX_ROW] = {};
      }else{
        labyrinth[randomPositionID]=AFF_VIDE;
        genRandomAlreadyConnexe[randomPositionID]=1;
      }
      recursionCount++;
    }while(wallToBuildRemaining>0&&recursionCount<=maxRecursion);
    
    if(recursionCount>=maxRecursion){
      printf("%s\n","Erreur : limite de récursion pour la génération du labyrithne atteinte");
    }
  }
}

// --------------------------------------------------------------------

int main(){
  gen_lab(33);
  affiche();
  return 0;
}

