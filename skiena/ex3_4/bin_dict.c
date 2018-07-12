#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bin_dict.h"

struct dict* dict_init(unsigned int size){	
	struct dict *dict = (struct dict*)malloc(sizeof(struct dict));
	dict->nbuckets  = (unsigned int)ceil(size/sizeof(byte));
	dict->size = size;
	dict->buckets = (byte*)malloc((sizeof(byte)*dict->nbuckets)+1);
	memset(dict->buckets, 0, sizeof(byte)*dict->nbuckets);
	return dict;
}

struct dict* dict_free(struct dict *dict){
	free(dict->buckets);
	free(dict);
	return NULL;
}
/* bucket_offset: Given a key return bucket in dict and its offset*/  
static int bucket_offset(struct dict *dict, int k, int *bucket, int *offset){
	if(k > dict->size)	
		return OUT_OF_BOUNDS;
	
	*offset = k%sizeof(byte);
	*bucket = (int)k/(sizeof(byte));	
	return OK;
}

int dict_search(struct dict *dict, int k){
	int bucket, offset, res;
	byte p;
	
	if( (res = bucket_offset(dict, k, &bucket, &offset)) != OK)
		return res;
	
	p = 0x1 << offset;
	p &= dict->buckets[bucket];
	
	if (p == 0x0)
		return KEY_NOT_FOUND;
	return OK;
}

int dict_insert(struct dict *dict, int k){
	int bucket, offset, res;
	byte p;
	
	if( (res = bucket_offset(dict, k, &bucket, &offset)) != OK)
		return res;
	
	p = 0x1 << offset;
	dict->buckets[bucket] |= p;	
	return OK;
}

int dict_delete(struct dict *dict, int k){
	int bucket, offset, res;
	byte p;
	
	if( (res = bucket_offset(dict, k, &bucket, &offset)) != OK)
		return res;
	
	p = !(0x1 << offset);
	dict->buckets[bucket] &= p;	
	return OK;
}


void dict_print(struct dict *dict) {
	int i, j;
	printf("------------\nDict Info:\n Size : %u\n------------\n", dict->size);
	for (i=0; i<dict->nbuckets-1; i++){
		for (j=0; j<sizeof(byte); j++){
			printf("[%d] -> [%d]\n", (int)(i*sizeof(byte)+j), (int)(((0x1<<j)&dict->buckets[i]))>>j);
		}
	}	
	for(j=0; j<(dict->size%dict->nbuckets); j++){
		printf("[%d] -> [%d]\n", (int)((dict->nbuckets-1)*sizeof(byte)+j), (int)(((0x1<<j)&dict->buckets[dict->nbuckets-1]))>>j);
	}
}	

