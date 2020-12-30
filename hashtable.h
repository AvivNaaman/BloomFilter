#ifndef INC_14_HASHTABLE_H
#define INC_14_HASHTABLE_H
#include <stdbool.h>

typedef struct {
	int size;
	int function_num;
	bool *table;
} hash_table;

hash_table *init_table(int size, int functions_count);

void insert_table(hash_table *table, char *value);

bool is_in_table(hash_table *table, char *value);

void free_table(hash_table*);

#endif
