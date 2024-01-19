/* Auteur du projet : Metroidzeta
	- Tout d'abord, installer la bibliothèque GMP (fichier "gmp.h" dans le dossier /include, et "libgmp-10.dll" dans le dossier /lib)
	Pour compiler :
		> gcc -Wall -I include -o prog *.c -L lib -lgmp-10
	Pour exécuter :
		> ./prog
*/
#include "arraylist.h"

arraylist_t * arraylist_create() {
	arraylist_t * a = malloc(sizeof(arraylist_t));
	if(!a) {
		perror("Echec d'allocation de l'arraylist");
		exit(EXIT_FAILURE);
	}
	a->data = malloc(sizeof(mpz_t) * ARRAYLIST_INITIAL_CAPACITY);
	if(!a->data) {
		perror("Echec d'allocation de memoire du tableau de l'arraylist");
		free(a); // On vide l'allocation précédente
		exit(EXIT_FAILURE);
	}
	a->capacity = ARRAYLIST_INITIAL_CAPACITY;
	a->size = 0;
	return a;
}

void arraylist_free(arraylist_t * a) {
	for(int i = 0; i < a->size; i++) {
		mpz_clear(a->data[i]);
	}
	free(a->data);
	free(a);
}

bool arraylist_needToEnlargeCapacity(arraylist_t * a) {
	if(a->size == a->capacity) {
		a->capacity *= 2;
		a->data = (mpz_t*) realloc(a->data,sizeof(mpz_t) * a->capacity);
		if(!a->data) {
			perror("Echec de reallocation de memoire du tableau de l'arraylist");
			return false; // Erreur
		}
	}
	return true;
}

bool arraylist_add(arraylist_t * a, mpz_t x) {
	if(!arraylist_needToEnlargeCapacity(a)) { return false; }
	mpz_init_set(a->data[a->size++],x); // a->data[a->size++] = x
	return true;
}

bool arraylist_addPos(arraylist_t * a, mpz_t x, int pos) {
	if(!arraylist_needToEnlargeCapacity(a) || pos < 0 || pos > a->capacity) {
		return false; // Erreur
	}
	for(int i = a->size; i > pos; i--) {
		mpz_init_set(a->data[i],a->data[i - 1]); // a->data[i] = a->data[i - 1]
	}
	mpz_init_set(a->data[pos],x); // a->data[pos] = x
	a->size++;
	return true;
}

int arraylist_getMiddleIndexDichotomous(arraylist_t * a, mpz_t x) {
	int left = 0;
	int right = a->size - 1;
	int middle = 0;

	while(left <= right) {
		middle = left + (right - left) / 2;
		int cmp = mpz_cmp(a->data[middle],x);

		if(cmp == 0) { // Si a->data[middle] == x, l'élément est présent dans le tableau, retournez -1
			return -1;
		}
		if(cmp > 0) { // Si a->data[middle] > x, l'élément recherché est plus petit, recherchez dans la moitié gauche
			right = middle - 1;
		} else { // Sinon, recherchez dans la moitié droite
			left = middle + 1;
		}
	}

	return middle; // Si l'élément n'est pas présent dans le tableau, retournez l'index du dernier milieu calculé
}

bool arraylist_isEmpty(arraylist_t * a) { return a->size == 0; }

bool arraylist_contains(arraylist_t * a, mpz_t x) {
	return arraylist_getMiddleIndexDichotomous(a,x) == -1; // Renvoie true si l'élement existe déjà (si la fonction renvoie -1)
}

void arraylist_addDichotomous(arraylist_t * a, mpz_t x) { // Ajoute l'élement dans le set en respectant l'ordre croissant (tableau trié)
	if(arraylist_isEmpty(a) || mpz_cmp(x,a->data[a->size - 1]) > 0) { // Si l'arraylist est vide ou x > a->data[a->size - 1]
		arraylist_add(a,x);
		return;
	}

	int middleIndex = arraylist_getMiddleIndexDichotomous(a,x);
	if(middleIndex != -1) { // Si l'élement n'existe pas déjà
		if(mpz_cmp(x,a->data[middleIndex]) < 0) { // Si x < a->data[middleIndex]
			arraylist_addPos(a,x,middleIndex);
		} else {
			arraylist_addPos(a,x,middleIndex + 1);
		}
	}
}