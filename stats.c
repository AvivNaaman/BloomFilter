#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

#define FILE_LINES 233270
#define LINE_LENGTH 100
typedef struct {
	char *word;
	bool was_used;
} string;

void read_to_arr(string *arr[], FILE *f) {
	char temp[100];
	for (int i = 0; i < FILE_LINES; ++i) {
		fgets(temp, LINE_LENGTH, f);
		temp[strcspn(temp, "\r\n")] = 0;
		arr[i] = (string *) malloc(sizeof(string));
		arr[i]->word = malloc((strlen(temp) + 1) * sizeof(char));
		strcpy(arr[i]->word, temp);
		arr[i]->was_used = false;
	}
}

void random_string(char *destination, int length) {
	char src[] = "0123456789!@#$%^&*().,";
	for (int i = 0; i < length-1; ++i) {
		*(destination++) = rand() % (sizeof(src)-1);
	}
	*destination = '\0';
}

double analyzeN(int n, int m, int k, string *insert[FILE_LINES], string *check[FILE_LINES]) {
	hash_table *table = init_table(m, k);
	for (int i = 0; i < n; ++i) {
		int indx = rand() % (FILE_LINES - 1);
		if (insert[indx]->was_used == false) {
			insert_table(table, insert[indx]->word);
			insert[indx]->was_used = true;
		} else {
			// random weird string, 14-digit
			char temp[15];
			random_string(temp, 15);
			insert_table(table, temp);
		}
	}

	int checks, invalids = 0;
	for (checks = 0; checks < FILE_LINES; ++checks) {
		if (is_in_table(table, check[checks]->word)) {
			invalids++;
		}
	}

	double part = ((double) invalids) / ((double) checks);

	for (int i = 0; i < FILE_LINES; ++i) {
		insert[i]->was_used = false;
	}

	return part;
}

void analyzeM(int m, int k, string *insert[FILE_LINES], string *check[FILE_LINES]) {
	printf("%d", m);
	bool already1 = false;
	for (int n = 50; n < 500000; n += 16666) {
		if (already1) {
			printf(",1.0");
		} else {
			double res = analyzeN(n, m, k, insert, check);
			printf(",%f", res);
			if (res > 0.98) already1 = true;
		}
	}
}

void analyzeK(int k, string *insert[FILE_LINES], string *check[FILE_LINES]) {
	for (int n = 50; n < 500000; n += 16666)
		printf(",%d", n);
	puts("");
	for (int m = 50; m < 500000; m += 20000) {
		analyzeM(m, k, insert, check);
		puts("");
	}
}

int main() {
	string *insert[FILE_LINES], *check[FILE_LINES];
	FILE *insert_file = fopen("input/long2.txt", "r");
	FILE *check_file = fopen("input/long1.txt", "r");
	read_to_arr(insert, insert_file);
	read_to_arr(check, check_file);

	for (int k = 1; k < 14; k += 4) {
		puts("");
		puts("");
		printf("K = %d:\n", k);
		analyzeK(k, insert, check);
	}


	printf("READ.");
}