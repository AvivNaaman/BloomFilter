#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "murmur.h"
#include "hashtable.h"

void bulk_call(char *filename, hash_table *table, void (*function)(hash_table *table, char *value));

void check_and_print(hash_table *table, char *value);

int main() {
	unsigned int m, K;
	char temp[100];

	// Enter m, scan string & convert to integer
	puts("Enter m (Hash table size): ");
	fgets(temp, 20, stdin);
	m = strtol(temp, NULL, 10);

	// Enter K, same:
	puts("Enter K (Hash table size): ");
	fgets(temp, 20, stdin);
	K = strtol(temp, NULL, 10);

	hash_table *table = init_table(m, K);

	// Insertions file name
	puts("Enter input file name of values to insert_table: ");
	fgets(temp, 100, stdin);
	temp[strcspn(temp, "\r\n")] = 0; // remove newline
	bulk_call(temp, table, insert_table);
	
	// Check file name
	puts("Enter input file name of values to check: ");
	fgets(temp, 100, stdin);
	temp[strcspn(temp, "\r\n")] = 0; // remove newline
	bulk_call(temp, table, check_and_print);

	free_table(table);
	return 0;
}

void check_and_print(hash_table *table, char *value) {
	bool exists = is_in_table(table, value);
	if (exists) printf("%s exists.\n", value);
	//else printf("%s does not exists.\n", value);
}

void bulk_call(char *filename, hash_table *table,
			   void (*function)(hash_table *table, char *value)) {
	char token[100];
	int curr_char, index;
	// open input file
	FILE *csv = fopen(filename, "r");
	if (csv == NULL) {
		fprintf(stderr, "File %s cannot be opened.", filename);
		exit(1);
	}
	// parses comma-seperated values & call the callback function
	for (curr_char = fgetc(csv), index = 0;; curr_char = fgetc(csv), index++) {
		if (curr_char == ',' || curr_char == EOF) { // comma or EOF
			token[index] = '\0';
			function(table, token);
			index = -1; // back to start - because will be ++ on next iteration
			if (curr_char == EOF) break; // if EOF - exit.
		}
		else {
			token[index] = curr_char;
		}
	}
	fclose(csv);
}
