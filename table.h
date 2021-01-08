#ifndef INC_14_TABLE_H
#define INC_14_TABLE_H
#include <stdbool.h>

/**
 * Represents a single table
 */
typedef struct {
	/**
	 * The table size [m]
	 */
	int size;
	/**
	 * The function number [K]
	 */
	int function_num;
	/**
	 * The bit array
	 */
	bool *table;
} hash_table;

/**
 * Initializes a single table & allocates all of it's required resources.
 * Returns NULL on failure.
 * @param size The size of the table [m]
 * @param functions_count The number of hash functions [K]
 * @return A pointer to the newly created table
 */
hash_table *init_table(int size, int functions_count);

/**
 * Inserts a value into the table
 * @param table The table to insert into
 * @param value The value to insert
 */
void insert_table(hash_table *table, char *value);

/**
 * Checks whether a value was inserted to the table
 * @param table The table to check in
 * @param value The value to look for
 * @return Whether the value is in the table
 */
bool is_in_table(hash_table *table, char *value);

/**
 * Deallocates all the allocated resources for a table
 * @param table The table to free
 */
void free_table(hash_table *table);

#endif
