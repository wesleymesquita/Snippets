#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int val;
	struct node *next;
} node; 

node* reverse(node **head){
	if((*head) == NULL) return NULL;
	if((*head)->next == NULL) return *head;
	node *curr,*old_next, *next;
	curr = (*head);
	next = curr->next;
	old_next = NULL;
	for(;;){
		curr->next = old_next;
		old_next = curr;	
		if(next == NULL) break;
		curr = next;
		next = next->next;		
		//printf("curr == %d, next == %d\n", curr->val, next->val);	
	}
	(*head) = curr;	
	return *head;	
}

node* create(int *v, int sz){
	if(sz == 0) return NULL;
	node *head = (node*)malloc(sizeof(node));
	node *n = head;
	int i=0;
	head->val = v[i++];
	while(i<sz){
		n->next = (node*)malloc(sizeof(node));
		n->next->val = v[i++];
		n->next->next = NULL;
		n = n->next;
	}
	return head;
}

void destroy(node **head) {
	node *t;
	for(;;){
		if((*head) == NULL) return;
		t = (*head);
		(*head) = (*head)->next;
		free(t);
	}
}	

		
void print(node *head){
	node *t;
	if(head == NULL) return;
	t = head;
	for(;;){
		printf("%d ",t->val);
		t = t->next;
		if (t == NULL) break;
	}
	printf("\n");
}


int test(int n){
	int i,j;	
	
	for(i=0; i<n; i++){	
		printf("Testing %d\n", i);
		int *t = (int*)malloc(i*sizeof(int));
		for(j=0; j<i; j++)
			t[j] = j;	
		node *l = create(t, i); 			
		print(l);
		reverse(&l);
		print(l);
		free(t);
		destroy(&l);	
	}
}


int main(){
	test(10);
	return 0;
}
