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

#include "arraylist.h"

arraylist_t * arraylist_create() {
	arraylist_t * a = malloc(sizeof(arraylist_t));
	if (!a) {
		perror("Echec d'allocation de l'arraylist\n");
		exit(EXIT_FAILURE);
	}
	a->data = malloc(sizeof(mpz_t) * ARRAYLIST_INITIAL_CAPACITY);
	if (!a->data) {
		perror("Echec d'allocation de memoire du tableau de l'arraylist\n");
		free(a);
		exit(EXIT_FAILURE);
	}
	a->capacity = ARRAYLIST_INITIAL_CAPACITY;
	a->size = 0;
	return a;
}

void arraylist_free(arraylist_t *a) {
	if (!a) return;
	for (int i = 0; i < a->size; i++) {
		mpz_clear(a->data[i]);
	}
	free(a->data);
	free(a);
}

static void arraylist_enlargeCapacity(arraylist_t *a) {
	a->capacity *= 2;
	mpz_t * new_data = (mpz_t*) realloc(a->data, sizeof(mpz_t) * a->capacity);
	if (!new_data) {
		perror("Echec de reallocation de memoire du tableau de l'arraylist\n");
		exit(EXIT_FAILURE);
	}
	a->data = new_data;
}

void arraylist_add(arraylist_t *a, mpz_t x) {
	if (a->size == a->capacity) arraylist_enlargeCapacity(a);
	mpz_init_set(a->data[a->size++], x); // on insère x à la fin du tableau
}

bool arraylist_addPos(arraylist_t *a, mpz_t x, int pos) {
	if (pos < 0 || pos > a->size) return false; // pos en dehors des limites du tableau
	if (a->size == a->capacity) arraylist_enlargeCapacity(a);
	for (int i = a->size; i > pos; i--) { // On déplace les valeurs vers la droite une par une en partant de la fin
		mpz_init(a->data[i]);                  // on initialise la nouvelle case
		mpz_set(a->data[i], a->data[i - 1]);   // on copie la valeur de gauche vers la droite
	}
	mpz_init_set(a->data[pos], x); // on insère x à la bonne place
	a->size++;
	return true;
}

static int arraylist_findInsertIndexDichotomous(arraylist_t *a, mpz_t x) {
	int left = 0, right = a->size - 1; // index gauche et droite du tableau

	while (left <= right) {
		int mid = left + (right - left) / 2;
		int cmp = mpz_cmp(a->data[mid], x); // e = x ?

		if (cmp == 0) return -1; // e = x, déjà présent
		else if (cmp > 0) right = mid - 1; // e > x, recherchez dans la moitié gauche du tab
		else left = mid + 1; // e < x, recherchez dans la moitié droite du tab
	}

	return left; // non présent, retourne l'index adéquat
}

bool arraylist_isEmpty(arraylist_t *a) {
	return !a || a->size == 0;
}

bool arraylist_contains(arraylist_t *a, mpz_t x) {
	return arraylist_findInsertIndexDichotomous(a,x) == -1;
}

void arraylist_addDichotomous(arraylist_t *a, mpz_t x) { // Ajoute l'élement dans le set en respectant l'ordre croissant (tableau trié)
	if (arraylist_isEmpty(a) || mpz_cmp(x, a->data[a->size - 1]) > 0) { // Si l'arraylist est vide ou x > dernier élément
		arraylist_add(a, x);
		return;
	}

	int insertIndex = arraylist_findInsertIndexDichotomous(a, x);
	if (insertIndex != -1) { // Si l'élement n'existe pas déjà
		arraylist_addPos(a, x, insertIndex);
	}
}