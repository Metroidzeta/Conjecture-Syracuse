// Projet réalisé par Metroidzeta
//
// Tout d'abord: installer la bibliothèque gmp.
// Ou bien, mettre le fichier "gmp.h" dans le dossier /include, et le fichier "libgmp-10.dll" dans le dossier /lib
//
// Pour complier avec Windows: gcc -Wall -I include -o prog *.c -L lib -lgmp-10
// Pour exécuter: ./prog

#include "arraylist.h"
#include <string.h>
#include <ctype.h>

#define TAILLE_NOMBRE_INPUT 1000
#define TAB_SYRACUSE_TAILLE 10000

arraylist_t * syracuse_tab[TAB_SYRACUSE_TAILLE];

int hash(mpz_t x) {
	mpz_t temp;
	mpz_init(temp);
	mpz_mod_ui(temp,x,TAB_SYRACUSE_TAILLE); // temp = x % TAB_SYRACUSE_TAILLE
	int result = mpz_get_ui(temp);
	mpz_clear(temp);
	return result;
}

void syracuse_tab_create() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		syracuse_tab[i] = arraylist_create();
	}
}

void syracuse_tab_free() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		arraylist_free(syracuse_tab[i]);
	}
}

void syracuse_calcul(mpz_t x, arraylist_t * nombres_visites) {
	while(true) {
		gmp_printf("%Zd",x);
		arraylist_add(nombres_visites,x);

		if(arraylist_contains(syracuse_tab[hash(x)],x) || mpz_cmp_ui(x,1) == 0) { // Si x a déjà été calculé OU x = 1
			printf(" (fin | deja evalue)\n");
			break;
		} else if(mpz_even_p(x)) { // Si x est pair
			mpz_divexact_ui(x,x,2); // x = x / 2
		} else { // Sinon (si x est impair)
			mpz_mul_ui(x,x,3); // x = x * 3
			mpz_add_ui(x,x,1); // x = x + 1
		}
		printf("\n");
	}
}

void syracuse(mpz_t x) {
	if(mpz_cmp_ui(x,1) < 0) { // Si x < 1
		printf("Erreur: le nombre doit etre strictement positif (> 0)\n");
		return;
	}
	arraylist_t * nombres_visites = arraylist_create();
	gmp_printf("-- Syracuse de %Zd : --\n", x);
	syracuse_calcul(x,nombres_visites);

	for(int i = 0; i < nombres_visites->taille; i++) {
		arraylist_addSet_dichotomique(syracuse_tab[hash(nombres_visites->tab[i])],nombres_visites->tab[i]);
	}
	arraylist_free(nombres_visites);
}

void syracuse_tab_afficher() {
	for(int i = 0; i < TAB_SYRACUSE_TAILLE; i++) {
		for(int j = 0; j < syracuse_tab[i]->taille; j++) {
			gmp_printf("syracuse_tab[%d]->tab[%d] = %Zd\n",i,j,syracuse_tab[i]->tab[j]);
		}
	}
}

bool estNombre(const char * str) {
	if(str == NULL || str[0] == '\0') { // Si str est null ou vide, ce n'est pas un nombre
		return false;
	}

	int index = 0;
	while(str[index] != '\0') {
		if(!isdigit(str[index])) { // Le caractère n'est pas un chiffre
			return false;
		}
		index++;
	}

	return true;
}

void viderTampon() {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main() {
	syracuse_tab_create();

	mpz_t x;
	char input[TAILLE_NOMBRE_INPUT];

	while(true) {
		printf("Veuillez taper un nombre a tester (ou \"fin\" pour quitter) : ");
		if(fgets(input, TAILLE_NOMBRE_INPUT - 1, stdin) != NULL) {
			size_t len = strcspn(input,"\n");
			if(input[len] == '\n') {
				input[len] = '\0'; // Remplace le '\n' par un '\0' pour supprimer la nouvelle ligne
			} else {
				viderTampon();
			}

			if(strcmp(input,"fin") == 0 || strcmp(input,"end") == 0) { // Si l'utilisateur écrit "fin" ou "end"
				break;
			}

			if(estNombre(input)) {
				mpz_init_set_str(x,input,10);
				syracuse(x);
				//syracuse_tab_afficher();
				mpz_clear(x);
			} else {
				printf("Erreur: Ce n'est pas un nombre\n");
			}
		} else {
			 printf("Erreur: mauvaise saisie\n");
		}
	}

	printf("Fin du programme\n");
	syracuse_tab_free();

	return EXIT_SUCCESS;
}