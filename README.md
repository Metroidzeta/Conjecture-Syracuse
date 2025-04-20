# Conjecture-Syracuse
Projet entièrement réalisé par Metroidzeta.  
La [Conjecture de Syracuse](https://fr.wikipedia.org/wiki/Conjecture_de_Syracuse) (appelé aussi conjecture de Collatz, ou encore conjecture d'Ulam) en C avec la bibliothèque [GMP](https://fr.wikipedia.org/wiki/GNU_MP) pour manipuler de très grands nombres et la [programmation dynamique](https://fr.wikipedia.org/wiki/Programmation_dynamique) pour éviter de recalculer les mêmes entiers en réutilisant les résultats précédents.  
Bien sûr, la programmation dynamique est utile uniquement si on test plusieurs nombres à la suite sans fermer le programme.  

Le but du projet est de recréer la Conjucture de Syracuse en C pour vérifier si n'importe quel entier strictement positif (> 0) fini par atteindre 1 ou non, afin de déterminer si la conjecture est vraie.  

## POUR DEMARRER LE PROGRAMME

Tout d’abord compiler : ```gcc -Wall -I include -o prog *.c -L lib -lgmp-10```  
Puis exécuter : ```./prog```  

Une fois le programme démarré, on vous demandera de taper un nombre positif :  
```Veuillez taper un nombre a tester (ou taper "fin" pour quitter) :```  

Exemple avec 17 :  

```
Veuillez taper un nombre a tester (ou taper "fin" pour quitter) : 17
-- Syracuse de 17 : --
17
52
26
13
40
20
10
5
16
8
4
2
1 (deja evalue)
```
## BIBLIOTHEQUE GMP

La bibliothèque [GMP](https://fr.wikipedia.org/wiki/GNU_MP) est obligatoire et doit être installé pour exécuter ce programme.  
Elle permet de taper des très grands nombres, mêmes ceux supérieurs à 2^64 - 1 (codé sur 64 bits), exemple : 10^24.  
Vous pouvez l'installer ou bien mettre manuellement le fichier "gmp.h" dans le dossier /include, et le fichier "libgmp-10.dll" dans le dossier /lib  