#include <stdio.h>

#define MAX_COLUMN 4  // Longeur de la grille (nombre de colonnes)
#define MAX_ROW 3     // Largeur de la grille (nombre de lignes)
#define AFF_VIDE '-'  // Caractère représentant les cases vides pour l’affichage
#define AFF_MUR 'X'   // Caractère représentant les murs pour l’affichage
#define AFF_BORD ' '  // Caractère représentant les bords pour l’affichage
#define POP_VALUE 0   // Valeur utiliser pour dépiler un entier
#define PUSH_VALUE 2  // Valeur utiliser pour empiler un entier

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

int pile[MAX_COLUMN*MAX_ROW];

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
  vérifie si toutes les cases blanches sont bien connectées entre elles
  * return {int} 0 si elles sont bien connéctées, 1 sinon
*/
int connexe(){
  int realWhiteSquareCount = 0;
  int randomSquareID=0;
  for(int x=0;x<MAX_ROW;x++){
    for(int y=0;y<MAX_COLUMN;y++){
      int id = getID(x,y);
      if(labyrinth[id] == AFF_VIDE){
        push(x);
        realWhiteSquareCount++;
        randomSquareID=id;
      }
    }
    if(realWhiteSquareCount == 0){
      printf("%d\n","Erreur aucune case blanche");
      return 0;
    }else{
      return detectedWhiteSquareCount(randomSquareID)==realWhiteSquareCount;
    }
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
  if(square_up_id!=-1){
    int square_up_value = pop(square_up_id);
    if(square_up_value==PUSH_VALUE){
      whiteCount+=detectedWhiteSquareCount(square_up_id);
    }
  }

  if(square_down_id!=-1){
    int square_down_value = pop(square_down_id);
    if(square_down_value==PUSH_VALUE){
      whiteCount+=detectedWhiteSquareCount(square_down_id);
    }
  }

  if(square_left_id!=-1){
    int square_left_value = pop(square_left_id);
    if(square_left_value==PUSH_VALUE){
      whiteCount+=detectedWhiteSquareCount(square_left_id);
    }
  }

  if(square_right_id!=-1){
    int square_right_value = pop(square_right_id);
    if(square_right_value==PUSH_VALUE){
      whiteCount+=detectedWhiteSquareCount(square_right_id);
    }
  }

  return whiteCount;
}

/*
  retourne l'id de la case au dessus de celle donnée en paramètre
  * {int} id de la case
  * return {int}
*/
int getUpSquareID(int id){
  int up_ID = id+MAX_ROW;
  if(up_ID>(MAX_ROW*MAX_COLUMN-1)){
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
  if(down_ID<0){
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
  if(left_ID<0){
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
  if(right_ID>(MAX_ROW*MAX_COLUMN-1)){
    return -1;
  }else{
    return right_ID;
  }
}

// --------------------------------------------------------------------

void gen_lab(){

}

// --------------------------------------------------------------------

int main(){
  affiche();
  return 0;
}

