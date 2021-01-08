#include <string.h>
#include "table.h"
#include "murmur.h"
#include <stdlib.h>

/**
 * - Internal - Implementation of the hash family.
 * Returns the hash of a specific value by the table size,
 * The seed & the value, normalized to fit table indices.
 * @param m The table size
 * @param seed The seed
 * @param value The value to hash
 * @return The hash of the value
 */
unsigned int hash_to_cell(int m, int seed, char *value) {
	uint32_t hash_val;
	int length = strlen(value);
	MurmurHash3_x86_32(value, length, seed, &hash_val); /* Base hash */
	return hash_val % m; /* Normalize to fit bounds of array */
}

void insert_table(hash_table *table, char *value) {
	/* for each hash function h_i() (which is represented by seed, the value (i-1)) */
	for (int i = 0; i < table->function_num; ++i) {
		/* hash and turn bit on */
		unsigned int cell = hash_to_cell(table->size, i, value);
		table->table[cell] = true;
	}
}

bool is_in_table(hash_table *table, char *value) {
	/* Same - iterate over the seeds (And therefore over the hash functions) */
	for (int i = 0; i < table->function_num; ++i) {
		/* hash, if value in index is false then it was never inserted */
		unsigned int cell = hash_to_cell(table->size, i, value);
		if (table->table[cell] == false) {
			return false;
		}
	}
	/* all true - it's in */
	return true;
}

hash_table *init_table(int size, int functions_count) {
	/* allocate bit table & struct, check allocation */
	bool *content = (bool*)malloc(size*sizeof(bool));
	hash_table *table = (hash_table *)malloc(sizeof(hash_table));
	if (content == NULL || table == NULL) {
		return NULL; /* Failure - allocation failed! */
	}

	/* Reset the allocated content - it has unknown data ("junk") */
	memset(content, false, sizeof(bool) * size);
	/* Set table properties */
	table->table = content;
	table->size = size;
	table->function_num = functions_count;
	return table;
}

void free_table(hash_table *to_free) {
	/* Deallocate internal bit table & then struct */
	free(to_free->table);
	free(to_free);
}