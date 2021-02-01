#include <stdio.h>
#include <cstring>

/*
Réalisez une fonction toUpper qui accepte un paramètre désignant une chaine de caractères et qui remplace, dans cette chaîne, toutes les lettres
minuscules par les majuscules correspondantes. Par exemple « Tim et Tom » devient « TIM ET TOM ».

Vous devez vous rappeler que la notation ‘À représente un entier de type char dont la valeur est le code ASCII de la lettre A. Et pareillement pour tous
les caractères imprimables. Vous n'avez donc PAS besoin d'une table de cades ASCII pour traiter cet exercice. Si vous avez besoin d'utiliser le code ASCII
de la lettre z, i suffit d'utiliser la notation ‘2°.

Pour savoir si une variable € de type char représente une lettre majuscule, on peut faire le test

if((c >= 'A') 86 (c <= ‘2')).

D'autre part, dans la table des codes ASCII (dont vous navez PAS besoin pour traiter cet exercice), les codes des lettres majuscules se suivent, de même
que ceux des lettres minuscules. I en résulte que (‘a'-'A') = ('b'-'B') = (‘c'-'C') = .… et donc si une variable € de type char contient le code
ASCII d'une lettre minuscule, le code ASCII de la lettre majuscule correspondante est c-(‘a'-"A)
*/

char* toUpper(char str0[]){
  int shouldContinue = 1;
  int index = 0;
  do{
    shouldContinue = str0[index]!=0;
    if(shouldContinue){
      if(str0[index]>'Z'){
        str0[index]-=32;
        printf("%c\n",str0[index]);
      }
    }
    index+=1;
  }while(shouldContinue);
  return str0;
}

int main(){
  char str0[] = "coucou";
  printf("%s\n",toUpper(str0));
  return 0;
}