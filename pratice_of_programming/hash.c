/* 
The code below was directly copied from 

Brian W. Kernighan and Rob Pike. 1999. 
The Practice of Programming. 
Addison-Wesley Longman Publishing Co., Inc., Boston, MA, USA.

** OR ** it is result of my attempt to solve book exercise,  
complete missing code and test its ideas

*/

/* Below I have done some code to test basic hash set 
operations, testing, retrieving and report. To deal with 
collisions, Iĺl TPOP approach of using linked lists on each 
entry */ 


/* 2.9 Hash Tables */

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

/* BEGIN - HASH TABLE */

struct hash_table *hash_table_alloc(int nhash)
{
	int i;
	struct hash_table *hash_table= (struct hash_table*)malloc(
									sizeof(struct hash_table));
	hash_table->symtab = (struct hash_entry**)malloc(
									sizeof(struct hash_entry*)*nhash);
	hash_table->nhash = nhash;
	for(i=0; i<nhash; i++)
		hash_table->symtab[i] = NULL;
	
	return hash_table;
}

void hash_table_free(struct hash_table *hash_table)
{
	int i;
	struct hash_entry *entry;
	for(i=0; i<hash_table->nhash; i++){
		while(hash_table->symtab[i] != NULL){
			entry = hash_table->symtab[i]->next;
			free(hash_table->symtab[i]);
			hash_table->symtab[i] = entry;
		}
	}
	free(hash_table->symtab);
	free(hash_table);	
}

void hash_table_print(struct hash_table *hash_table, 
						void (*print_data)(void* data))
{
	int i;
	struct hash_entry *sym;
	for(i=0; i<hash_table->nhash; i++){
		sym = hash_table->symtab[i];
		printf("[ %d ] :\n", i);
		while(sym != NULL){
			print_data(sym->data);
			sym = sym->next;
			if (sym != NULL)
				printf(" -> ");
		}	
		printf("\n");
	}		
}


struct hash_entry* hash_table_lookup(struct hash_table *table, 
	void* data, unsigned int (*data_hash)(void* data, int nhash),
	int (*datacmp)(void *d1, void *d2)) 
{
	unsigned int h;  
	struct hash_entry *sym;  
	h = data_hash(data, table->nhash);  
		
	for (sym = table->symtab[h]; sym != NULL; sym = sym->next) {
		if (datacmp(data, sym->data) == 0) {
			return sym;  	
		}
	}
	return NULL;
}

struct hash_entry* hash_table_insert(struct hash_table* table, void *data, 
	unsigned int (*data_hash)(void* data, int nhash), 
	int (*datacmp)(void *d1, void *d2))
{
	struct hash_entry *sym;
	int hash_key;

	hash_key = data_hash(data, table->nhash);
	
	if(!hash_table_lookup(table, data, data_hash, datacmp)){
		sym = (struct hash_entry*) malloc(sizeof(struct hash_entry));  
		sym->data = data;
		sym->next = table->symtab[hash_key];  
		table->symtab[hash_key] = sym; 
		return sym;
	}
	return NULL;
}

/* END - HASH TABLE */
