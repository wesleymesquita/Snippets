
/**
Implementation of 

3-4. [3] Design a dictionary data structure in which search, insertion, and deletion can all be processed in O(1) time in the worst case. You may assume the set elements are integers drawn from a i nite set 1,2,..,n, and initialization can take O(n) time.

From 

@book{Skiena:2008:ADM:1410219,
 author = {Skiena, Steven S.},
 title = {The Algorithm Design Manual},
 year = {2008},
 isbn = {1848000693, 9781848000698},
 edition = {2nd},
 publisher = {Springer Publishing Company, Incorporated},
} 

**/


#define OK 0
#define OUT_OF_BOUNDS -1
#define KEY_NOT_FOUND -2    

/* Assuming sizeof(char) == size of a byte, but really doesn't matter */
typedef char byte;

/* struct dict : each dict entry is a bit */
struct dict {
	byte *buckets;
	unsigned int size;
    unsigned int nbuckets;
};

/* init_dict : alloc memory for a new dict  and 
initializes it. Return initialized pointer */
struct dict* dict_init(unsigned int size);

/* dict_free : frees memory allocated for a struct dict. 
Return NULL if all freed or return dict if failed */
struct dict* dict_free(struct dict *dict);

/* dict_search: search for entry n. Return OK, OUT_OF_BOUNDS or KEY_NOT_FOUND */
int dict_search(struct dict *dict, int k);

/* dict_insert : insert entry n. Return OK or OUT_OF_BOUNDS */
int dict_insert(struct dict *dict, int k);

/* dict_delete : delete entry n. Return OK or OUT_OF_BOUNDS */ 
int dict_delete(struct dict *dict, int k); 

/* dict_print : print dictionary representation in format 
KEY -> [0|1]
*/
void dict_print(struct dict *dict);
