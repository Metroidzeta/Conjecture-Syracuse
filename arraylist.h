// Projet réalisé par Metroidzeta

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h> // La bibiothèque qui permet de manipuler de très grands nombres (> 64 bits)

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define ARRAYLIST_INITIAL_CAPACITY 4

typedef struct arraylist_s {
	mpz_t * tab; // Le tableau qui contient les éléments (mpz_t = très grands nombres)
	int capacite; // Taille réelle (capacité de stockage) du tableau
	int taille; // Nombre d'éléments actuellement stockés dans le tableau
} arraylist_t;

arraylist_t * arraylist_create();
void arraylist_free(arraylist_t * a);
bool arraylist_need_to_enlarge_capacity(arraylist_t * a);
bool arraylist_add(arraylist_t * a, mpz_t x);
bool arraylist_add_pos(arraylist_t * a, mpz_t x, int pos);
int arraylist_getIndexMilieu_dichotomique(arraylist_t * a, mpz_t x);
bool arraylist_isEmpty(arraylist_t  * a);
bool arraylist_contains(arraylist_t * a, mpz_t x);
void arraylist_addSet_dichotomique(arraylist_t * a, mpz_t x);

#endif