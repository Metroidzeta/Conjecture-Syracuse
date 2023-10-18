// Projet réalisé par Metroidzeta

#include "arraylist.h"

arraylist_t * arraylist_create() {
	arraylist_t * a = malloc(sizeof(arraylist_t));
	if(!a) {
		perror("Echec d'allocation de l'arraylist");
		exit(EXIT_FAILURE);
	}
	a->tab = malloc(sizeof(mpz_t) * ARRAYLIST_INITIAL_CAPACITY);
	if(!a->tab) {
		perror("Echec d'allocation de memoire du tableau de l'arraylist");
		free(a); // on vide l'allocation précédente
		exit(EXIT_FAILURE);
	}
	a->capacite = ARRAYLIST_INITIAL_CAPACITY;
	a->taille = 0;
	return a;
}

void arraylist_free(arraylist_t * a) {
	for(int i = 0; i < a->taille; i++) {
		mpz_clear(a->tab[i]);
	}
	free(a->tab);
	free(a);
}

bool arraylist_need_to_enlarge_capacity(arraylist_t * a) {
	if(a->taille == a->capacite) {
		a->capacite *= 2;
		a->tab = (mpz_t*) realloc(a->tab,sizeof(mpz_t) * a->capacite);
		if(!a->tab) {
			perror("Echec de reallocation de memoire du tableau de l'arraylist");
			return false; // erreur
		}
	}
	return true;
}

bool arraylist_add(arraylist_t * a, mpz_t x) {
	if(!arraylist_need_to_enlarge_capacity(a)) {
		return false; // erreur
	}
	mpz_init_set(a->tab[a->taille],x); // a->tab[a->taille] = x
	a->taille++;
	return true;
}

bool arraylist_add_pos(arraylist_t * a, mpz_t x, int pos) {
	if(!arraylist_need_to_enlarge_capacity(a) || pos < 0 || pos > a->capacite) {
		return false; // erreur
	}
	for(int i = a->taille; i > pos; i--) {
		mpz_init_set(a->tab[i],a->tab[i - 1]); //a->tab[i] = a->tab[i - 1]
	}
	mpz_init_set(a->tab[pos],x); // a->tab[pos] = x
	a->taille++;
	return true;
}

int arraylist_getIndexMilieu_dichotomique(arraylist_t * a, mpz_t x) {
	int gauche = 0;
	int droite = a->taille - 1;
	int milieu = 0;

	while(gauche <= droite) {
		milieu = gauche + (droite - gauche) / 2;
		int cmp = mpz_cmp(a->tab[milieu],x);

		if(cmp == 0) { // a->tab[milieu] == x, si l'élément est présent dans le tableau, retournez -1
			return -1;
		}

		if(cmp > 0) { // a->tab[milieu] > x, si l'élément recherché est plus petit, recherchez dans la moitié gauche
			droite = milieu - 1;
		} else { // Sinon, recherchez dans la moitié droite
			gauche = milieu + 1;
		}
	}

	return milieu; // Si l'élément n'est pas présent dans le tableau, retournez l'index du dernier milieu calculé
}

bool arraylist_isEmpty(arraylist_t * a) {
	return a->taille == 0;
}

bool arraylist_contains(arraylist_t * a, mpz_t x) {
	return arraylist_getIndexMilieu_dichotomique(a,x) == -1; // Si cette fonction renvoie -1 alors l'élement existe déjà
}

void arraylist_addSet_dichotomique(arraylist_t * a, mpz_t x) { // Ajout d'un élement dans le Set en respectant l'ordre croissant
	if(arraylist_isEmpty(a)) {
		arraylist_add(a,x);
		return;
	}

	int milieu = arraylist_getIndexMilieu_dichotomique(a,x);
	if(milieu != -1) { // Si l'élement n'existe pas déjà
		if(mpz_cmp(x,a->tab[milieu]) < 0) { // si x < a->tab[milieu]
			arraylist_add_pos(a,x,milieu);
		} else {
			arraylist_add_pos(a,x,milieu + 1);
		}
	}
}