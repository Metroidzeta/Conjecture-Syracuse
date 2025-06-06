/* 
 * @author Alain Barbier alias "Metroidzeta"
 * 
 * - Tout d'abord, installer la bibliothèque GMP (ou l'importer)
 * 
 * Pour compiler :
 *     > gcc -Wall -I include -L lib -o prog *.c -lgmp-10
 * Pour exécuter :
 *     > ./prog
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h> // Bibliothèque GMP qui permet de manipuler de très grands nombres (> 64 bits)

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define ARRAYLIST_INITIAL_CAPACITY 4

typedef struct arraylist_s {
	mpz_t * data; // Tableau qui contient les éléments (mpz_t = très grands nombres)
	int capacity; // Taille réelle (capacité de stockage) du tableau
	int size; // Nombre d'éléments actuellement stockés dans le tableau
} arraylist_t;

arraylist_t * arraylist_create();
void arraylist_free(arraylist_t *a);
void arraylist_add(arraylist_t *a, mpz_t x);
bool arraylist_addPos(arraylist_t *a, mpz_t x, int pos);
bool arraylist_isEmpty(arraylist_t  *a);
bool arraylist_contains(arraylist_t *a, mpz_t x);
void arraylist_addDichotomous(arraylist_t *a, mpz_t x);

#endif