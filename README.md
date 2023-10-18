# Conjecture-Syracuse
Projet entièrement réalisé par Metroidzeta.  
La [Conjecture de Syracuse](https://fr.wikipedia.org/wiki/Conjecture_de_Syracuse) (appelé aussi conjecture de Collatz, ou encore conjecture d'Ulam) en C avec de la [programmation dynamique](https://fr.wikipedia.org/wiki/Programmation_dynamique) pour éviter de recalculer les mêmes entiers en réutilisant les résultats précédents.  
Evidemment, la programmation dynamique est utile seulement si on test plusieurs nombres à la suite sans fermer le programme.  

Le but du projet est de créer à partir de 0 la Conjucture de Syracuse en C afin de vérifier n'importe quel entier strictement positif (> 0) si il fini par atteindre 1 ou non, pour déterminer si la conjecture est vraie.  

## POUR DEMARRER LE PROGRAMME

Tout d’abord compiler : ```gcc -Wall -I include -o prog *.c -L lib -lgmp-10```  
Puis exécuter : ```./prog```  

## BIBLIOTHEQUE GMP

La bibliothèque [GMP](https://fr.wikipedia.org/wiki/GNU_MP) est obligatoire et doit être installé pour exécuter ce programme.  
Vous pouvez l'installer manuellement ou bien mettre le fichier "gmp.h" dans le dossier /include, et le fichier "libgmp-10.dll" dans le dossier /lib  