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
#include <string.h>
#include <ctype.h>

#define SIZE_NUMBER_INPUT 1000
#define SIZE_ARRAY_SYRACUSE 10000

arraylist_t *syracuse_arrayNumbers[SIZE_ARRAY_SYRACUSE];

unsigned int hash(mpz_t x) {
	return mpz_fdiv_ui(x, SIZE_ARRAY_SYRACUSE);
}

void syracuse_createArray() {
	for (int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		syracuse_arrayNumbers[i] = arraylist_create();
	}
}

void syracuse_freeArray() {
	for (int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		arraylist_free(syracuse_arrayNumbers[i]);
	}
}

void syracuse_calcul(mpz_t x, arraylist_t *visited_numbers) {
	while (true) {
		gmp_printf("%Zd", x); // On affiche le nombre
		if (arraylist_contains(syracuse_arrayNumbers[hash(x)], x) || mpz_cmp_ui(x,1) == 0) { // Si x a déjà été calculé OU x = 1
			printf(" (deja evalue)\n");
			break;
		}
		arraylist_add(visited_numbers, x); // Ajoute le nombre visité

		if (mpz_even_p(x)) { // x est pair
			mpz_divexact_ui(x, x, 2); // x = x / 2
		} else { // x est impair
			mpz_mul_ui(x, x, 3); // x = x * 3
			mpz_add_ui(x, x, 1); // x = x + 1
		}
		printf("\n");
	}
}

void syracuse(const mpz_t input) {
	arraylist_t *visited_numbers = arraylist_create();
	mpz_t x;
    mpz_init_set(x, input);

	gmp_printf("-- Syracuse de %Zd : --\n", x);
	syracuse_calcul(x, visited_numbers);

	for (int i = 0; i < visited_numbers->size; i++) {
		arraylist_addDichotomous(syracuse_arrayNumbers[hash(visited_numbers->data[i])], visited_numbers->data[i]);
	}

	mpz_clear(x);
	arraylist_free(visited_numbers);
}

void syracuse_printArray() { // For debug
	for (int i = 0; i < SIZE_ARRAY_SYRACUSE; i++) {
		for (int j = 0; j < syracuse_arrayNumbers[i]->size; j++) {
			gmp_printf("syracuse_arrayNumbers[%d]->data[%d] = %Zd\n", i, j, syracuse_arrayNumbers[i]->data[j]);
		}
	}
}

bool is_strictly_positive_number(const char *str)  {
	if (!str || str[0] == '\0') return false; // Str null ou vide -> ce n'est pas un nombre

	int index = 0;
	bool only_zeros = (str[0] == '0'); // Premier caractère est un 0

	while (str[index] != '\0') {
		if (!isdigit(str[index])) { // Le caractère n'est pas un chiffre
			return false;
		}
		if (only_zeros && str[index] != '0') { // Vérifier si ce n'est pas que des 0
			only_zeros = false;
		}
		index++;
	}

	return !only_zeros;
}

void clear_stdin_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
	syracuse_createArray();

	mpz_t x;
	mpz_init(x);
	char input[SIZE_NUMBER_INPUT];

	while (true) {
		printf("Veuillez taper un nombre a tester (ou taper \"fin\" pour quitter) : ");

		if (fgets(input, SIZE_NUMBER_INPUT - 1, stdin) != NULL) {
			size_t len = strcspn(input, "\n");
			if (input[len] == '\n') {
				input[len] = '\0'; // Remplace le '\n' par un '\0' pour supprimer la nouvelle ligne
			} else {
				clear_stdin_buffer();
			}

			if (strcmp(input, "fin") == 0 || strcmp(input, "end") == 0) { // Si l'utilisateur écrit "fin" ou "end"
				break;
			}

			if (is_strictly_positive_number(input)) {
				mpz_set_str(x, input, 10);
				syracuse(x);
				//syracuse_printArray(); // For debug
			} else {
				printf("Erreur : Ce n'est pas un nombre strictement positif (> 0).\n");
			}
		} else {
			  printf("Erreur : Saisie invalide.\n");
		}
	}

	printf("Fin du programme\n");
	mpz_clear(x);
	syracuse_freeArray();

	return EXIT_SUCCESS;
}