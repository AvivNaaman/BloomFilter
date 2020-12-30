#include <string.h>
#include "hashtable.h"
#include "murmur.h"
#include <stdlib.h>

unsigned int hash_to_cell(int m, int seed, char *value) {
	uint32_t hash_val;
	int length = strlen(value);
	MurmurHash3_x86_32(value, length, seed, &hash_val);
	return hash_val % m;
}

void insert_table(hash_table *table, char *value) {
	for (int i = 0; i < table->function_num; ++i) {
		unsigned int cell = hash_to_cell(table->size, i, value);
		table->table[cell] = true;
	}
}

bool is_in_table(hash_table *table, char *value) {
	for (int i = 0; i < table->function_num; ++i) {
		unsigned int cell = hash_to_cell(table->size, i, value);
		if (table->table[cell] == false) {
			return false;
		}
	}
	return true;
}

hash_table *init_table(int size, int functions_count) {
	bool *content = (bool*)malloc(size*sizeof(bool));
	hash_table *table = (hash_table *)malloc(size*sizeof(hash_table));
	if (content == NULL || table == NULL) {
		return NULL; // Failure
	}
	memset(content, false, sizeof(bool) * size); // reset all to false
	table->table = content;
	table->size = size;
	table->function_num = functions_count;
	return table;
}

void free_table(hash_table *to_free) {
	free(to_free->table);
	free(to_free);
}