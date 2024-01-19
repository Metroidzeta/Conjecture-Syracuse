/* Auteur du projet : Metroidzeta
	- Tout d'abord, installer la bibliothèque GMP (fichier "gmp.h" dans le dossier /include, et "libgmp-10.dll" dans le dossier /lib)
	Pour compiler :
		> gcc -Wall -I include -o prog *.c -L lib -lgmp-10
	Pour exécuter :
		> ./prog
*/
#include "arraylist.h"
#include <string.h>
#include <ctype.h>

#define SIZE_NUMBER_INPUT 1000
#define SIZE_ARRAY_SYRACUSE 10000

arraylist_t * syracuse_arrayNumbers[SIZE_ARRAY_SYRACUSE];

int hash(mpz_t x) {
	mpz_t temp;
	mpz_init(temp);
	mpz_mod_ui(temp,x,SIZE_ARRAY_SYRACUSE); // temp = x % SIZE_ARRAY_SYRACUSE
	int result = mpz_get_ui(temp);
	mpz_clear(temp);
	return result;
}

void syracuse_createArray() {
	for(int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		syracuse_arrayNumbers[i] = arraylist_create();
	}
}

void syracuse_freeArray() {
	for(int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		arraylist_free(syracuse_arrayNumbers[i]);
	}
}

void syracuse_calcul(mpz_t x, arraylist_t * visited_numbers) {
	while(true) {
		gmp_printf("%Zd",x);
		arraylist_add(visited_numbers,x);

		if(arraylist_contains(syracuse_arrayNumbers[hash(x)],x) || mpz_cmp_ui(x,1) == 0) { // Si x a déjà été calculé OU x = 1
			printf(" (deja evalue)\n");
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
	arraylist_t * visited_numbers = arraylist_create();
	gmp_printf("-- Syracuse de %Zd : --\n", x);
	syracuse_calcul(x,visited_numbers);

	for(int i = 0; i < visited_numbers->size; i++) {
		arraylist_addDichotomous(syracuse_arrayNumbers[hash(visited_numbers->data[i])],visited_numbers->data[i]);
	}
	arraylist_free(visited_numbers);
}

void syracuse_printArray() {
	for(int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		for(int j = 0; j < syracuse_arrayNumbers[i]->size; j++) {
			gmp_printf("syracuse_arrayNumbers[%d]->data[%d] = %Zd\n",i,j,syracuse_arrayNumbers[i]->data[j]);
		}
	}
}

bool isStrictlyPositiveNumber(const char * str) {
	if(str == NULL || str[0] == '\0') { return false; } // Si str est null ou vide, ce n'est pas un nombre

	int index = 0;
	bool zeroOnly = (str[0] == '0');
	while(str[index] != '\0') {
		if(!isdigit(str[index])) { // Le caractère n'est pas un chiffre
			return false;
		}
		if(zeroOnly && str[index] != '0') { // Vérifier si ce n'est pas que des 0
			zeroOnly = false;
		}
		index++;
	}

	return !zeroOnly;
}

void emptyBuffer() {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main() {
	syracuse_createArray();
	mpz_t x;
	char input[SIZE_NUMBER_INPUT];

	while(true) {
		printf("Veuillez taper un nombre a tester (ou taper \"fin\" pour quitter) : ");
		if(fgets(input, SIZE_NUMBER_INPUT - 1, stdin) != NULL) {
			size_t len = strcspn(input,"\n");
			if(input[len] == '\n') {
				input[len] = '\0'; // Remplace le '\n' par un '\0' pour supprimer la nouvelle ligne
			} else {
				emptyBuffer();
			}

			if(strcmp(input,"fin") == 0 || strcmp(input,"end") == 0) { // Si l'utilisateur écrit "quitter", "fin" ou "end"
				break;
			}

			if(isStrictlyPositiveNumber(input)) {
				mpz_init_set_str(x,input,10);
				syracuse(x);
				//syracuse_printArray();
				mpz_clear(x);
			} else {
				printf("Erreur: ce n'est pas un nombre strictement postif (> 0)\n");
			}
		} else {
			 printf("Erreur: mauvaise saisie\n");
		}
	}

	printf("Fin du programme\n");
	syracuse_freeArray();

	return EXIT_SUCCESS;
}