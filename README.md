# Conjecture-Syracuse
Projet entièrement réalisé par Metroidzeta.
La [Conjecture de Syracuse](https://fr.wikipedia.org/wiki/Conjecture_de_Syracuse) (appelé aussi conjecture de Collatz, ou encore conjecture d'Ulam)  
en C avec de la [programmation dynamique](https://fr.wikipedia.org/wiki/Programmation_dynamique) pour éviter de recalculer les mêmes entiers en réutilisant les résultats précédents.  
Evidemment, la [programmation dynamique](https://fr.wikipedia.org/wiki/Programmation_dynamique) est utile uniquement si on fait plusieurs appels à syracuse() à la suite sans fermer le programme.  

Le but du projet est de créer à partir de 0 la conjucture de syracuse en C  
afin de vérifier n'importe quel entier strictement positif (> 0) si il fini par atteindre 1 ou non, pour déterminer si la conjecture est vraie.  

## POUR DEMARRER LE PROGRAMME

Tout d’abord compiler : ```gcc -Wall arraylist.c syracuse.c -o prog.exe```  
Puis exécuter : ```./prog```  