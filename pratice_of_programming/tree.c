
/* 
The code below was directly copied from 

Brian W. Kernighan and Rob Pike. 1999. 
The Practice of Programming. 
Addison-Wesley Longman Publishing Co., Inc., Boston, MA, USA.

OR it is result of my attempt to solve an exercise and 
complete missing code

*/

/* 2.8 - Trees */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Use a base value for all tests. If needed take it from command
line */
static int DATA_SZ = (1<<20);


int weprintf(const char *format, ...);
void eprintf(const char *format, ...);

/* BEGIN of excerpts of TPOP code */

typedef struct Nameval Nameval;
struct Nameval {
	const char *name;
	int value;
	Nameval *left; /* lesser */
	Nameval *right; /* greater */
};

Nameval *insert(Nameval *treep, Nameval *newp)  
{  
	int cmp;  
	if (treep == NULL)  
		return newp;  
	cmp = strcmp(newp->name, treep->name);  
	if (cmp == 0)  
		weprintf("insert: duplicate entry %s ignored",  newp->name);  
	else if (cmp < 0)  
		treep->left = insert(treep->left, newp);  
	else  
		treep->right = insert(treep->right, newp);  
	return treep;  
}

Nameval *insert_by_value(Nameval *treep, Nameval *newp)  
{  
	if (treep == NULL)  
		return newp;  
	if (treep->value == newp->value)  
		weprintf("insert: duplicate entry %s ignored",  newp->name);  
	else if (treep->value > newp->value)  
		treep->left = insert_by_value(treep->left, newp);  
	else  
		treep->right = insert_by_value(treep->right, newp);  
	return treep;  
}
/* lookup: look up name in tree treep */  
Nameval *lookup(Nameval *treep, const char *name)  
{  
	int cmp;  
	if (treep == NULL)  
		return NULL;  
	cmp = strcmp(name, treep->name);  
		if (cmp == 0)  
		return treep;  
	else if (cmp < 0)  
		return lookup(treep->left, name);  
	else  
		return lookup(treep->right, name);  
}

/* nrlookup: non-recursively look up name in tree treep */  
Nameval *nrlookup(Nameval *treep, char *name)  
{  
	int cmp;  
	while (treep != NULL) {  
		cmp = strcmp(name, treep->name);  
		if (cmp == 0)  
			return treep;  
		else if (cmp < 0)  
			treep = treep->left;  
		else  
			treep = treep->right;  
	}  
	return NULL;  
}

/* applyinorder: inorder application of fn to treep */  
void applyinorder(Nameval *treep,  void (*fn)(Nameval*, void*), void *arg)  
{  
	if (treep == NULL)  
		return;  
	applyinorder(treep->left, fn, arg);  
	(*fn)(treep, arg);  
	applyinorder(treep->right, fn, arg);  
}

/* applypostorder: postorder application of fn to treep */  
void applypostorder(Nameval *treep,  void (*fn)(Nameval*, void*), void *arg)  
{  
	if (treep == NULL)  
		return;  
	applypostorder(treep->left, fn, arg);  
	applypostorder(treep->right, fn, arg);  
	(*fn)(treep, arg);  
}


/* END of excerpts of TPOP code */


void clean_up_tree(Nameval *tree, void *param)
{
	free((void*)tree->name);
	free(tree);
}

Nameval *insert_int(Nameval *tree, int val, int by_value){
	Nameval *new_node = (Nameval*)malloc(sizeof(Nameval));
	new_node->value = val;
	/* it is a waste of space to pre alloc 16, i
	but worth to get coding done faster */
	new_node->name = (const char*)malloc(16*sizeof(char)); 
	sprintf((char*)new_node->name, "%d", new_node->value);
	new_node->left = NULL;
	new_node->right = NULL;
	if (by_value)
		return insert_by_value(tree, new_node);
	return insert(tree, new_node);
}


void eprintf(const char *format, ...) {
	va_list valist;	
	va_start(valist, format);	

	fprintf(stderr, format, valist);	
	va_end(valist);
	exit(EXIT_FAILURE);
}

int weprintf(const char *format, ...){	
	char* warn_format;
	int ret_val; 
	va_list valist;
	
	warn_format = (char*)malloc(strlen("WARNING :") + strlen(format));
	strcpy(warn_format, "WARNING :");
	strcat(warn_format, format);
		
	va_start(valist, format);	
	ret_val = fprintf(stdout, warn_format, valist);
	free(warn_format);
	va_end(valist);	
	
	return 	ret_val;
}

void populate_random_array(int *data, char **data_str, int sz){
	int *data_in, i, t;
	data_in = (int*)malloc(sizeof(int)*sz);
	memset((void*)data_in, 0, sizeof(int)*sz);
	/* populate array, to be used in both tests */
	srand((unsigned int)time(NULL));
	for(i=0; i<sz; i++){
		t = rand()%sz;
		/* grants that numbers will be unique. Use data_in
		as a hash */
		while (data_in[t] != 0)
			t = rand()%sz;
		data_in[t] = 1;
		data[i] = t; 
		sprintf(data_str[i], "%d", i);	
	}	 
	free(data_in);
}

void exercise_2_11()
{

	printf("***Starting exercise 2-11\n");
	/* Compare the performance of `lookup' and `nrlookup'. How expansive is recursion
	compared to iteration? */

	/* Test strategy : 

	1) Add DATASZ random items in tree and record those items in a array. 
	2) Record current time (t0)
	3) Iterate over the DATASZ items and call `lookup'
	4) Get time delta from t0.
	5) Record current time (t0)
	6) Iterate over the DATASZ items and call `nrlookup'
	7) Get time delta from t0.
	8) Output deltas from lookup and nrloopku and compare boths.

	Result : compiling without optimization, the result was a 20% faster 
			 execution for non-recursive approach. Using -O1, -O2 or -O3, 
			 the time is the same;
	*/

	clock_t start, end, rec, non_rec;
	int *data, i, j, t;
	char **data_str;	
	
	data = (int*)malloc(sizeof(int)*DATA_SZ);
	data_str = malloc(sizeof(char**)*DATA_SZ);
	for(i=0; i<DATA_SZ; i++)
		data_str[i] = (char*)malloc(16*sizeof(char));
		
	populate_random_array(data, data_str, DATA_SZ);

	Nameval *tree = insert_int(NULL, data[0], 0);
	for(i=1; i<DATA_SZ; i++)
		tree = insert_int(tree, data[i], 0);	
	
	start = clock();
	for(i=0; i<DATA_SZ; i++){
		Nameval *n = lookup(tree, data_str[i]);
		if(n == NULL){
			applypostorder(tree, clean_up_tree, NULL);	
			eprintf("Value %s must be on tree\n", data_str[i]);
		}	
	}	
	end = clock();
	rec = end-start;
	printf("Total time to run recursive lookupl:\t%10.6f\n", 
					(double)(rec)/CLOCKS_PER_SEC);	

	start = clock();
	for(i=0; i<DATA_SZ; i++){
		Nameval *n = nrlookup(tree, data_str[i]);
		if(n == NULL){
			applypostorder(tree, clean_up_tree, NULL);	
			eprintf("Value %s must be on tree\n", data_str[i]);
		}	
	}	
	end = clock();
	non_rec = end-start;
	printf("Total time to run non-recursive lookup:\t%10.6f\n", 
					(double)(non_rec)/CLOCKS_PER_SEC);	
	printf("Relation non-recursive time / recursive\t%10.6f\n", 
				(double)non_rec/rec);	
	
	applypostorder(tree, clean_up_tree, NULL);	
	
	free(data);
	for(i=0; i<DATA_SZ; i++)
		free(data_str[i]);
	free(data_str);

	printf("***Ended exercise 2-11\n");
}

/* BEGIN Auxiliary functions to Exercise 2.12 */

struct array_data{
	int *array;
	int pos;
};

void insert_in_array(Nameval *treep, void *arr_data){
	struct array_data *data = (struct array_data*)arr_data;
	data->array[data->pos] = treep->value;
	data->pos++;
}

void print_int_array(int *arr, int sz){
	int i;
	printf("-->\n"); 
	for(i=0; i<sz; i++)
		printf(" [%d] ", arr[i]);
	printf("\n<--\n"); 
}

int cmp_int(const void *a, const void *b){
	return *(int*)a-*(int*)b;
}
	
/* END Auxiliary functions to Exercise 2.12 */

void exercise_2_12()
{
	printf("***Starting exercise 2-12\n");
	/**
	Testing strategy : 
	1) Create an array with random integers
	2) Input array in tree
	3) Replace array with in-order traversal. Final array must be sorted. 
	*/
	
	clock_t start, end, tree_time, qsort_time;
	int *unsorted_data, *data, i;
	
	char **data_str;	
	data_str = (char**)malloc(sizeof(char*)*DATA_SZ);
	for(i=0; i<DATA_SZ; i++)
		data_str[i] = malloc(sizeof(char)*16);
	unsorted_data = (int*)malloc(sizeof(int)*DATA_SZ);	
	data = (int*)malloc(sizeof(int)*DATA_SZ);
	populate_random_array(unsorted_data, data_str, DATA_SZ);
	
	/* print_int_array(unsorted_data, DATA_SZ); */
	
	start = clock(); 
	/* tree building is part of algorithm timingi, 
	so, will consider the time to build it*/
	Nameval *tree = insert_int(NULL, unsorted_data[0], 1);
	for(i=1; i<DATA_SZ; i++)
		insert_int(tree, unsorted_data[i], 1);

	struct array_data adata;
	adata.array = data;
	adata.pos = 0;	
	/* Will apply in order orginal function to add elements to 
	sorted array */
	applyinorder(tree, insert_in_array, &adata);
	end = clock();	
	
	/* check if `data' is really sorted */
	/* for(i=1; i<DATA_SZ; i++){
		if(data[i-1]>data[i]){
			print_int_array(data, DATA_SZ);
			eprintf("Error... this method is not sorting\n");
		}
	} */
	tree_time = end-start;
	printf("Ordering `by tree' took\t%10.6lf seconds\n", (double)tree_time/CLOCKS_PER_SEC);

	start = clock();
	qsort(unsorted_data, DATA_SZ, sizeof(int), cmp_int);
	end = clock();
	qsort_time = end-start;
	printf("Ordering `by qsort' took\t%10.6lf seconds\n", (double)qsort_time/CLOCKS_PER_SEC);
	printf("Relation to `by tree'/ `by qsort':\t%10.6f\n", (double)tree_time/qsort_time);
	
	for(i=0; i<DATA_SZ; i++)
		free(data_str[i]);
	free(data_str);
	free(unsorted_data);
	free(data);
	printf("***Ended exercise 2-12\n");
}

void exercise_2_13()
{
	printf("Exercise 2-13: We used the provided tree functions from TOP in last two exercises, they showed correct\n");
}
int main(int argc, char **argv)
{
	if(argc > 1){
		DATA_SZ = atoi(argv[1]);
	}
	exercise_2_11();		
	exercise_2_12();
	exercise_2_13();
	return 0;
}

