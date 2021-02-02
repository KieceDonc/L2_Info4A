/*
Réalisez en C une fonction main qui :
- crée un chaîne “Tim " (au format C) dans un tableau dynamique 
  dont l'adresse sera placée dans une variable sl, 
- crée un chaîne “et Tom" (au format C) dans un tableau dynamique 
  dont l'adresse sera placée dans une variable s2,
- appelle la fonction concat pour créer une chaîne dynamique contenant 
  la concaténation des chaînes désignées par sl et s2 et place l'adresse 
  de cette nouvelle chaîne dans une variable s3.
- affiche avec printf la chaîne désignée par s3.
- libère toute la mémoire occupée par les chaînes ayant été créées.
Attention, pour placer une chaîne dans un tableau créé dans le tas, il faut utiliser strcpy.
On ne peut pas directement initialiser un tableau dynamique avec une chaîne comme on
peut le faire avec un tableau automatique.
*/