// Projet réalisé par Metroidzeta

#include "arraylist.h"

#define TAB_SYRACUSE_TAILLE 10000

arraylist_t * syracuse_tab[TAB_SYRACUSE_TAILLE];

int hash(unsigned long long int x) {
	return x % TAB_SYRACUSE_TAILLE;
}

void syracuse_tab_create() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		syracuse_tab[i] = arraylist_create();
	}
}

void syracuse_tab_free() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		arraylist_free(syracuse_tab[i]);
		syracuse_tab[i] = NULL;
	}
}

void syracuse_calcul(unsigned long long int x, arraylist_t * nombres_visites) {
	while(true) {
		printf("%I64u\n",x); //! --> remplacer %I64u par %llu si vous n'êtes pas sur Windows avec mingw
		arraylist_add(nombres_visites,x);

		if(arraylist_contains(syracuse_tab[hash(x)],x) || x == 1) { // Si x a déjà été calculé ou que x = 1
			break;
		} else if(x % 2 == 0) { // Si x est pair
			x /= 2;
		} else { // Sinon (si x est impair)
			x = x * 3 + 1;
		}
	}
}

void syracuse(unsigned long long int x) {
	if(x < 1) {
		printf("ERREUR: le nombre doit etre strictement positif (> 0) et inferieur a la valeur maximum d'un unsigned long long int (<= 18446744073709551615)\n");
		return;
	}
	arraylist_t * nombres_visites = arraylist_create();
	printf("-- Syracuse de %I64u : --\n",x); //! --> remplacer %I64u par %llu si vous n'êtes pas sur Windows avec mingw
	syracuse_calcul(x,nombres_visites);

	for(int i = 0; i < nombres_visites->taille; i++) {
		arraylist_addSet_dichotomique(syracuse_tab[hash(nombres_visites->tab[i])],nombres_visites->tab[i]);
	}
	arraylist_free(nombres_visites);
}

void syracuse_tab_afficher() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		for(int j = 0; j < syracuse_tab[i]->taille; j++) {
			printf("syracuse_tab[%d]->tab[%d] = %I64u\n",i,j,syracuse_tab[i]->tab[j]); //! --> remplacer %I64u par %llu si vous n'êtes pas sur Windows avec mingw
		}
	}
}

int main(int argc, char *argv[]) {
	syracuse_tab_create();

	syracuse(1000000000);
	syracuse_tab_afficher();

	syracuse_tab_free();

	return EXIT_SUCCESS;
}