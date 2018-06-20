
/** HASH TABLE */

/* struct hash_entry : represent each data representation in 
hash table */
struct hash_entry 
{  
	void *data; /* Points to the data */
	struct hash_entry *next; /* Linked list */  
};  

/* struct hash_table */
struct hash_table
{
	struct hash_entry **symtab; /* a symbol table */
	int nhash;
};

/* hash_table_alloc : dynamically allocates memory for a hash table.
Note : as nhash is the number of hash slots, better chose a prime 
number and reduce collisions */
struct hash_table *hash_table_alloc(int nhash);

/* hash_table_free : frees all memory allocated in a hash_table */
void hash_table_free(struct hash_table *hash_table);

/* hash_table_print : prints contents */
void hash_table_print(struct hash_table *hash_table, 
						void (*print_data)(void* data));

/* lookup: find name in symtab, with optional create */  
struct hash_entry* hash_table_lookup(struct hash_table *hash_table, 
	void* data, unsigned int (*data_hash)(void* data, int nhash),
	int (*datacmp)(void *d1, void *d2));

/* hash_table_insert : insert data on hash_table.*/  
struct hash_entry* hash_table_insert(struct hash_table* table, void *data, 
	unsigned int (*data_hash)(void* data, int nhash),
    int (*datacmp)(void *d1, void *d2));

