// Projet réalisé par Metroidzeta

#include "arraylist.h"

arraylist_t * arraylist_create() {
	arraylist_t * a = malloc(sizeof(arraylist_t));
	if(!a) {
		fprintf(stderr,"Echec d'allocation de l'arraylist\n");
		exit(EXIT_FAILURE); // quitter le programme
	}
	a->tab = malloc(sizeof(unsigned long long int) * ARRAYLIST_INITIAL_CAPACITY);
	if(!a->tab) {
		fprintf(stderr,"Echec d'allocation de memoire du tableau de l'arraylist\n");
		free(a); // on vide l'allocation précédente
		exit(EXIT_FAILURE); // quitter le programme
	}
	a->capacite = ARRAYLIST_INITIAL_CAPACITY;
	a->taille = 0;
	return a;
}

void arraylist_free(arraylist_t * a) {
	if(a) {
		if(a->tab) {
			free(a->tab);
			a->tab = NULL; // Définir a->tab à NULL après la libération
		}
		free(a);
	}
}

bool arraylist_need_to_enlarge_capacity(arraylist_t * a) {
	if(a->taille == a->capacite) {
		a->capacite *= 2;
		a->tab = (unsigned long long int *) realloc(a->tab,sizeof(unsigned long long int) * a->capacite);
		if(!a->tab) {
			fprintf(stderr,"Echec de reallocation de memoire du tableau de l'arraylist\n");
			return false; // erreur
		}
	}
	return true;
}

bool arraylist_add(arraylist_t * a, unsigned long long int x) {
	if(!a || !arraylist_need_to_enlarge_capacity(a)) {
		return false; // erreur
	}
	a->tab[a->taille++] = x;
	return true;
}

bool arraylist_add_pos(arraylist_t * a, unsigned long long int x, int pos) {
	if(!a || !arraylist_need_to_enlarge_capacity(a) || pos < 0 || pos > a->capacite) {
		return false; // erreur
	}
	for(int i = a->taille; i > pos; i--) {
		a->tab[i] = a->tab[i - 1];
	}
	a->tab[pos] = x;
	a->taille++;
	return true;
}

int arraylist_getIndexMilieu_dichotomique(arraylist_t * a, unsigned long long int x) {
	int gauche = 0;
	int droite = a->taille - 1;
	int milieu = 0;

	while(gauche <= droite) {
		milieu = gauche + (droite - gauche) / 2;

		if(a->tab[milieu] == x) { // Si l'élément est présent dans le tableau, retournez -1
			return -1;
		}

		if(a->tab[milieu] > x) { // Si l'élément recherché est plus petit, recherchez dans la moitié gauche
			droite = milieu - 1;
		} else { // Sinon, recherchez dans la moitié droite
			gauche = milieu + 1;
		}
	}

	return milieu; // Si l'élément n'est pas présent dans le tableau, retournez l'index du dernier milieu calculé
}

bool arraylist_isEmpty(arraylist_t  * a) {
	return a->taille == 0;
}

bool arraylist_contains(arraylist_t * a, unsigned long long int x) {
	return a && arraylist_getIndexMilieu_dichotomique(a,x) == -1; // Si cette fonction renvoie -1 alors l'élement existe déjà
}

void arraylist_addSet_dichotomique(arraylist_t * a, unsigned long long int x) { // Ajout d'un élement dans le Set en respectant l'ordre croissant
	if(!a) { return; }
	if(arraylist_isEmpty(a)) {
		arraylist_add(a,x);
		return;
	}

	int milieu = arraylist_getIndexMilieu_dichotomique(a,x);
	if(milieu != -1) { // Si l'élement n'existe pas déjà
		if(x < a->tab[milieu]) {
			arraylist_add_pos(a,x,milieu);
		} else {
			arraylist_add_pos(a,x,milieu + 1);
		}
	}
}