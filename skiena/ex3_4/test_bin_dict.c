#include "bin_dict.h"
#include <stdio.h>

static const char* errors_s(int error_n){
    switch(error_n){
        case OK:
            return "OK";
            break;
        case OUT_OF_BOUNDS:
            return "OUT_OF_BOUNDS";
            break;
        case KEY_NOT_FOUND:
            return "KEY_NOT_FOUND";
            break;
        default:
            return "UNKOWN_ERROR";
    }
}

static int insert_all_delete_all(unsigned int N){
    struct dict *dict;
    int i, resp;
    dict = dict_init(N);

    for(i=1; i<=N; i++){ 
        resp = dict_insert(dict, i);
        if (resp != OK){
            fprintf(stderr, "Could not insert %d in dict. Got %s\n", 
                i, errors_s(resp));
            return resp;
        }
    }
     
    for(i=1; i<=N; i++){ 
        resp = dict_search(dict, i);
        if (resp != OK){
            fprintf(stderr, "Could not find %d in dict. Got %s\n", 
                i, errors_s(resp));
            return resp;
        }
    }
    
    for(i=1; i<=N; i++){ 
        resp = dict_delete(dict, i);
        if (resp != OK){
            fprintf(stderr, "Could not insert %d i in dict. Got %s\n", 
                i, errors_s(resp));
            return resp;
        }
    }
    
    dict_free(dict); 
    return OK;
}


int main(){
   int resp; 
   resp = insert_all_delete_all(200); 
   printf("Test result : %s\n", errors_s(resp));
   return 0;
}
