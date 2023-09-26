#include "arraylist.h"

arraylist_t * arraylist_create() {
	arraylist_t * a = malloc(sizeof(arraylist_t));
	a->tab = malloc(sizeof(unsigned long long int) * ARRAYLIST_INITIAL_CAPACITY);
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
			perror("erreur de reallocation du tableau arraylist");
			return false;
		}
	}
	return true;
}

bool arraylist_add(arraylist_t * a, unsigned long long int x) {
	if(!arraylist_need_to_enlarge_capacity(a)) {
		return false;
	}
	a->tab[a->taille++] = x;
	return true;
}

bool arraylist_add_pos(arraylist_t * a, unsigned long long int x, int pos) {
	if(!arraylist_need_to_enlarge_capacity(a)) {
		return false;
	}
	for(int i = a->taille - 1; i >= pos; i--) {
		a->tab[i + 1] = a->tab[i];
	}
	a->tab[pos] = x;
	a->taille++;
	return true;
}

int arraylist_getMilieuIndex_dichotomique(arraylist_t * a, unsigned long long int x) {
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

bool arraylist_contains(arraylist_t * a, unsigned long long int x) {
	return arraylist_getMilieuIndex_dichotomique(a,x) == -1;
}

void arraylist_addSet_dichotomique(arraylist_t * a, unsigned long long int x) { // Ajout d'un élement Set avec recherche dichotomique
	if(a->taille == 0) {
		arraylist_add(a,x);
		return;
	}

	int milieu = arraylist_getMilieuIndex_dichotomique(a,x);
	if(milieu != -1) {
		if(x < a->tab[milieu]) {
			arraylist_add_pos(a,x,milieu);
		} else {
			arraylist_add_pos(a,x,milieu + 1);
		}
	}
}