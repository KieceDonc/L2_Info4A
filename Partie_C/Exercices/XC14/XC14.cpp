#include <stdio.h>
#include <stdlib.h>

/*
On appelle permutation de taille n toute suite de n entiers dans laquelle chacune des valeurs
comprises entre O et n-l apparait exactement une fois. Par exemple 1,0,4,3,2 est une permutation 
de taille 5. Réalisez une fonction genPerm qui accepte deux paramètres : tab, qui désigne un tableau 
d'entiers, et n de type int. En supposant que n soit la taille du tableau, cette fonction doit 
remplir ce tableau avec une permutation de taille n produite aléatoirement. Cette fonction doit être 
aussi efficace que possible et faire appel au plus n fois à la fonction rand.
*/

/*
L'idée va être de généré un nombre aléatoire. Il va représente l'index du chiffre x que l'on va placer 
dans le tableau. Si le chiffre à l'index de l'aléatoire est déjà pris on incrémente l'index. Si l'index
dépasse la taille du tableau on le remet à 0 et on le laisse incrémenté si besoin. Quelque soit l'aléatoire 
le nombre x va toujours trouver une place dans le tableau
*/

void genPerm(int* tab, int n){
  for(int x=0;x<n;x++){
    srand(x);
    int index = ((double) rand())/RAND_MAX*n+1; // entre 0 et n inclus
    int canBePlaceAtIndex = 0;
    do{
      canBePlaceAtIndex = tab[index]==0;
      if(!canBePlaceAtIndex){
        canBePlaceAtIndex = false;
        index++;
        if(index>=n){
          index=0;
        }
      }
    }while(!canBePlaceAtIndex);
    tab[index]=x;
  }
}

void printTab(int* tab,int length){
  for(int x=0;x<length;x++){
    printf("%s%d %s %d\n","index n°",x,"=",tab[x]);
  }
}

int main(){
  int length = 10;
  int tab[length]={};
  genPerm(tab,length);
  printTab(tab,length);
  return 0;
}