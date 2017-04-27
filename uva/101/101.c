#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOVE_ONTO 0x0001
#define MOVE_OVER 0x0010
#define PILE_ONTO 0x0100
#define PILE_OVER 0x1000
#define QUIT 0x1111


struct block{
    int id;
    struct block *top, *down;
};

struct block* 
init_block(int id){
   struct block* b;

   b = (struct block*)malloc(sizeof(struct block));
   b->id = id;
   b->top = NULL;
   b->down = NULL;
   return b;
};

struct block_array{
    struct block** arr;
    struct block** blocks;
};



struct block_array*
create_block_array(int n){
    int i;
    struct block_array *a = (struct block_array*)malloc(sizeof(struct block_array));
    a->arr = (struct block**)malloc(n*sizeof(struct block*));
    a->blocks = (struct block**)malloc(n*sizeof(struct block*));

    for(i=0; i<n;i++){
        a->blocks[i]=init_block(i);
        a->arr[i]=a->blocks[i];
    }
    return a;
}

void 
destroy_block_array(struct block_array **array_ref, int n){
    int i;
    for(i=0;i<n;i++){
        free((*array_ref)->blocks[i]);
    }
    free((*array_ref)->arr);
    free((*array_ref)->blocks);
    free(*array_ref);
}

void 
print_block_array(struct block_array* ab, int n){
    int i;
    struct block *b;    
    for(i=0;i<n;i++){
        printf("%d:", i);
        b = ab->arr[i];
        while ( b!=NULL) {
            printf(" %d", b->id);
            b=b->top;
        }
        printf("\n");
    }
}

struct command{
    int id;
    int b1, b2;
};

void
parse_command(char *cmd_line, struct command *cmd){
    char cmd_text[16];
    sscanf(cmd_line, "%s %d %s %d", cmd_text, &cmd->b1, (char*)(void*)(cmd_text+4), &cmd->b2);
    if(strcmp(cmd_text, "moveonto") == 0)
        cmd->id=MOVE_ONTO;
    else if(strcmp(cmd_text, "moveover") == 0)
        cmd->id=MOVE_OVER;
    else if(strcmp(cmd_text, "pileonto") == 0)
        cmd->id=PILE_ONTO;
    else if(strcmp(cmd_text, "pileover") == 0)
        cmd->id=PILE_OVER;
    else
        cmd->id=QUIT;
}




void 
move_onto(struct block_array *barr, int ba, int bb){
    struct block *b, *top;
    b  = barr->blocks[ba];
    while(b != NULL){
        top = b->top;
        b->top = NULL;
        if(top != NULL)
            barr->arr[top->id] = top;
        b = top;
    }

    b  = barr->blocks[bb];
    while(b->top != NULL){
        top = b->top;
        b->top = NULL;
        if(top != NULL)
            barr->arr[top->id] = top;
        b = top;
    }
    barr->blocks[ba]->top = NULL;
    barr->blocks[bb]->top = barr->blocks[ba];
    barr->blocks[ba]->down = barr->blocks[bb];

    barr->arr[ba] = NULL;
}


void 
move_over(struct block_array *barr, int ba, int bb){
    struct block *b, *top;
    b  = barr->blocks[ba];
    while(b != NULL){
        top = b->top;
        b->top = NULL;
        if(top != NULL)
            barr->arr[top->id] = top;
        b = top;
    }
    
    b  = barr->blocks[bb];
    while(b->top != NULL){
        b = b->top;
    }
    barr->blocks[ba]->top = NULL; 
    b->top = barr->blocks[ba];
    barr->blocks[ba]->down = b;
    barr->arr[ba] = NULL;
}

void 
pile_onto(struct block_array *barr, int ba, int bb){
    struct block *b, *top;
    b  = barr->blocks[bb];
    while(b->top != NULL){
        top = b->top;
        b->top = NULL;
        if(top != NULL)
            barr->arr[top->id] = top;
        b = top;
    }
    barr->arr[bb]->top = barr->arr[ba]->top; 
    barr->arr[ba]->top->down = barr->arr[bb];
    barr->arr[ba]->top = NULL; 
}

void 
pile_over(struct block_array *barr, int ba, int bb){
    struct block *topb;

    topb  = barr->blocks[bb];
    while(topb->top != NULL){
        topb = topb->top;
    }
    topb->top = barr->arr[ba];
    if(barr->arr[ba]->down != NULL)
        barr->arr[ba]->down->top = NULL;
}


int main(){
    
    struct block_array *ba;
    struct command cmd;
    int n, quit;
    char cmd_line[16];
    
    scanf("%d\n", &n);
    ba = create_block_array(n);
    quit=0;
    for(;!quit;){
        fgets(cmd_line, 16, stdin);
        parse_command(cmd_line, &cmd);
        if(cmd.b1 == cmd.b2)
            continue;
        switch(cmd.id){
            case MOVE_ONTO:
                move_onto(ba, cmd.b1, cmd.b2);
                break;
            case MOVE_OVER:
                move_over(ba, cmd.b1, cmd.b2);
                break;
            case PILE_ONTO:
                pile_onto(ba, cmd.b1, cmd.b2);
                break;
            case PILE_OVER:
                pile_over(ba, cmd.b1, cmd.b2);
                break;
            case QUIT:
                quit=1;
                break;
        }
    }
    print_block_array(ba, n);
    destroy_block_array(&ba, n);

    return 0;
}
