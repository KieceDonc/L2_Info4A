/*
  gcc Valentin_VERSTRACTE_partie1.cpp -g -Wall -o Valentin_VERSTRACTE_partie1
  commande pour compiler
  
  ./Valentin_VERSTRACTE_partie1 
  commande pour exécuter
*/
#include <stdio.h>
#include <stdlib.h>
#define AFF_VIDE '-'  // Caractère représentant les cases vides pour l’affichage
#define AFF_MUR  'X'  // Caractère représentant les murs pour l’affichage
#define AFF_BORD 'M'  // Caractère représentant les bords pour l’affichage

int NB_COLONNES = 4; // Longueur de la grille(nombre de colonnes)
int NB_LIGNES = 3;   // Largeur de la grille(nombre de lignes)
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

int main()
{
  Grille = (char*)calloc(NB_LIGNES*NB_COLONNES,sizeof(char));
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
  free(Grille);
  return 0;
}
