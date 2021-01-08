#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"

/**
 * Maximum size of a single token in file
 */
#define MAX_TOKEN_SIZE 100

/**
 * Tokenizes a comma seperated values file and calls
 * the func argument with each tokenized value.
 * @param filename The CSV file name to tokenize
 * @param table The table to call the func with
 * @param func The function to call for each token in the file - gets table & current values as args.
 */
void bulk_call(char *filename, hash_table *table, void (*func)(hash_table *table, char *value));

/**
 * A helper function for bulk_call, which checks if
 * a value is in the table and prints if so.
 */
void check_and_print(hash_table *table, char *value);

/**
 * Entry Point
 */
int main() {
	unsigned int m, K; /* table size & function number */
	char temp[MAX_TOKEN_SIZE];

	/* Enter m, scan string & convert to integer */
	puts("Enter m (Hash table size): ");
	fgets(temp, MAX_TOKEN_SIZE, stdin);
	m = strtol(temp, NULL, 10);

	/* Enter K, same: */
	puts("Enter K (Function number): ");
	fgets(temp, MAX_TOKEN_SIZE, stdin);
	K = strtol(temp, NULL, 10);

	/* Init table & check for errors */
	hash_table *table = init_table(m, K);
	if (table == NULL) { /* failure */
		puts("Memory allocation failed.");
		exit(1);
	}

	/* Insertions file name */
	puts("Enter input file name of values to insert: ");
	fgets(temp, MAX_TOKEN_SIZE, stdin);
	temp[strcspn(temp, "\r\n")] = '\0'; /* remove "enter" */
	bulk_call(temp, table, insert_table);

	/* Checks file name */
	puts("Enter input file name of values to check: ");
	fgets(temp, MAX_TOKEN_SIZE, stdin);
	temp[strcspn(temp, "\r\n")] = '\0';
	bulk_call(temp, table, check_and_print);

	/* Done - free allocated memory */
	free_table(table);
	return 0;
}

void check_and_print(hash_table *table, char *value) {
	bool exists = is_in_table(table, value);
	if (exists) printf("%s exists.\n", value);
	else printf("%s does not exist.\n", value);
}

void bulk_call(char *filename, hash_table *table,
               void (*func)(hash_table *, char *)) {
	char token[MAX_TOKEN_SIZE];
	int curr_char, index;

	/* open input file & handle error */
	FILE *csv = fopen(filename, "r");
	if (csv == NULL) {
		fprintf(stderr, "\nFile %s cannot be opened", filename);
		exit(1);
	}

	/* copy the current token to token[] buffer. if end of token (comma/EOF), call the func.
	 * if EOF, end loop. "index" var holds current position in buffer. exit loop inside. */
	for (curr_char = fgetc(csv), index = 0;; curr_char = fgetc(csv), index++) {
		if (curr_char == ',' || curr_char == EOF) { // comma or EOF - next token
			token[index] = '\0';
			func(table, token);
			index = -1; /* back to start - because will index++ on next iteration */
			if (curr_char == EOF) break; /* if EOF/EOL - exit. */
		} else {
			token[index] = (char) curr_char; /* copy current char to token */
		}
	}

	/* Close file */
	fclose(csv);
}
