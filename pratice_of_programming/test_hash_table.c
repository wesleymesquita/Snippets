
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
/* BEGIN - functions ito handle char* in hash table*/

/* hash: compute hash value of string */  
unsigned int str_hash(void *data, int nhash)  
{  
	char *str;
	unsigned int h;  
	unsigned char *p;  
	const int MULTIPLIER = 31;

	str = (char*)data;
	h = 0;  
	for (p = (unsigned char *) str; *p != '\0'; p++)  
		h = MULTIPLIER * h + *p;  
	return h % nhash;  
}

/* str_print: to be used on hash_table_print */
void str_print(void *data)
{
	printf("%s", (char*)data);
}
/* str_cmp: */
int str_cmp(void *d1, void *d2)
{
	return strcmp((const char*)d1, (const char*)d2);
}

/* fill_random_string: fill string str with size str_sz with 
random lower case alpha characters */
void fill_random_string(char *str, int str_sz){
	int i, ascii_delta;
	char c;
	ascii_delta = 122-97;
	for(i=0; i<str_sz-1; i++){
		c = 97 + rand()%ascii_delta;
		str[i] = c;
	}
	str[str_sz-1] = '\0';
}

/* generate_random_strings: (returns an array of n_strings each 
with size in range [1..max_str_sz] */
char **generate_string_set(int n_strings, int max_str_sz)
{	
	int i, j, str_sz;
	char **set;

	srand(time(NULL));
	set = (char**)malloc(sizeof(char*)*n_strings);
	for(i=0; i<n_strings; i++){
		str_sz = rand()%max_str_sz + 2; /* str_size is at least 2 */
		set[i] = (char*)malloc(sizeof(char)*str_sz);
		fill_random_string(set[i], str_sz);
	}
	return set;			
}

/* print_string_set  : */
void print_string_set(char **string_set, int n_strings){
	int i;
	for(i=0; i<n_strings; i++)
		fprintf(stdout, "%10d\t%s\n", i, string_set[i]); 
}


/* clean_string_set: frees space allocated on  generate_random_strings */
void clean_string_set(char **set, int n_strings)
{
	int i;
	for(i=0; i<n_strings; i++)
		free(set[i]);
	free(set);			
}

/* END - functions ito handle char* in hash table*/
			

/* BEGIN - Collect and show statistics about hash table */
struct stat_hash_table
{
	struct hash_table table;
	int *stat_table;
	int nhash;
};

struct stat_hash_table* stat_hash_table_alloc(struct hash_table *table)
{
	struct stat_hash_table *stat;
	
	stat = (struct stat_hash_table*)malloc(sizeof(struct stat_hash_table));
	stat->nhash = table->nhash;
	stat->stat_table = (int*)malloc(sizeof(int)*stat->nhash);
	memset((void*)stat->stat_table, 0, sizeof(int)*stat->nhash);
	return stat;
}

void stat_hash_table_free(struct stat_hash_table *stat)
{
    free(stat->stat_table);
    free(stat);
}

void stat_hash_table_update(struct stat_hash_table *stat, int hash)
{
    stat->stat_table[hash]++;
}


void stat_hash_table_print(struct stat_hash_table *stat)
{
	int i;
	fprintf(stdout, "HASH KEY\tCOLISIONS\n");
	for(i=0; i<stat->nhash; i++){
		fprintf(stdout, "%10d\t%10d\n", i, stat->stat_table[i]);
    }
}


/* END - Collect and show statistics about hash table */

/* hash_table_load_test: 
    n_strings : how many strings to input and search
    max_str_sz  : maximum string size
    hash_table_size : slots for symbols table in hash table 
*/
void hash_table_load_test(int n_strings, int max_str_sz, int hash_table_size)
{
	char **str_set;
	int i;	
	clock_t start, end;
	int NHASH = hash_table_size;

	struct hash_table *table;
	struct stat_hash_table *stat;
	struct hash_entry *res;

	table = hash_table_alloc(NHASH);
	stat = stat_hash_table_alloc(table);
	str_set = generate_string_set(n_strings, max_str_sz);	

#ifdef DEBUG
	fprintf(stdout, "Using the followin as input for testing\n");
	print_string_set(str_set, n_strings);
#endif

    /* insert all in hash table */
	for(i=0; i<n_strings; i++){
		hash_table_insert(table, (void*)str_set[i], str_hash, str_cmp);  
        stat_hash_table_update(stat, str_hash((void*)str_set[i], NHASH));
	}
    
    /* must retrieve all */ 
	start = clock();			
	for(i=0; i<n_strings; i++){
		res = hash_table_lookup(table, (void*)str_set[i], str_hash, str_cmp);
        
		if(res == NULL || strcmp((const char*)res->data, str_set[i]) != 0){
			fprintf(stderr, "Error: %s not found\n", str_set[i]);
			exit(EXIT_FAILURE);
		}
	}
	end = clock();
    
    stat_hash_table_print(stat);
	fprintf(stdout, "Test time : Searched %d strings in seconds \t%11.6f\n", 
            n_strings, (double)(end-start)/CLOCKS_PER_SEC);
    
    clean_string_set(str_set, n_strings);
	stat_hash_table_free(stat);	
	hash_table_free(table);
}

/* hash_table_interactive_test: input strings from stdin in hashtable 
and follow table status*/
void hash_table_interactive_test()
{
	char str[256];
	struct hash_table *table;
	struct stat_hash_table *stat;	
    struct hash_entry *res;
	const int NHASH = 37;	
    int lookup; /* 0 - insert , 1 - lookup*/
    
    lookup = 0;	
	table =	hash_table_alloc(NHASH);
	stat = stat_hash_table_alloc(table);	
	
	printf("To change mode, type `c' or `q' to quit\n");
	for(;;){
        if(lookup) 
            printf("Lookup mode:");
        else 
            printf("Insert mode: ");
        
        scanf("%s", str);
        if(str[0] == 'c'){
            lookup = !lookup;
            continue;
        }
        else if(str[0] == 'q'){
            hash_table_free(table);
            stat_hash_table_free(stat);
            exit(EXIT_SUCCESS);
        }  
        if(lookup){
         
		    res = hash_table_lookup(table, (void*)str, str_hash, str_cmp);
        
            if(res == NULL || strcmp((const char*)res->data, str) != 0)
                fprintf(stderr, "Error: %s not found\n", str);
            else
                fprintf(stdout, "%s found!\n", str);
        }
        else{
            hash_table_insert(table, (void*)str, str_hash, str_cmp);
            stat_hash_table_update(stat, str_hash((void*)str, NHASH));
        }
   }
}


void exercise_2_14(){
}

void exercise_2_15(){
}

void exercise_2_16(){
}

void exercise_2_17(){
}


int main(int argc, char **argv)
{
    char op;
    int n_strings, max_str_sz, hash_table_size;
    n_strings = 10000;
    max_str_sz = 32;
    hash_table_size = 101;

    op = 'i';
	if(argc == 2)
        op = argv[1][0];
    if(op == 'i')    	
	    hash_table_interactive_test();
    else{
        op = 'z';
        while(op != 'y' && op != 'n'){
            printf("Use default values?[y/n]");
            scanf("%c", &op);
        }
        if(op == 'n'){
            printf("Number of strings: ");
            scanf("%d", &n_strings);
            printf("Max string size : ");
            scanf("%d", &max_str_sz);
            printf("Hash table size: ");
            scanf("%d", &hash_table_size); 
        }
        hash_table_load_test(n_strings, max_str_sz, hash_table_size); 
    }
	return 0;
}

