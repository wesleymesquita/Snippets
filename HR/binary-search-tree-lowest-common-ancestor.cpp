//https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor
/*
Node is defined as 

typedef struct node
{
   int data;
   node * left;
   node * right;
}node;

*/


node * lca(node * root, int v1,int v2)
{
    if(root == NULL){
        return NULL;
    }
    
    if( v1 == root->data || v2 == root->data){
        return root;
    }    
    else if( (v1<root->data && v2>root->data) || (v1>root->data && v2<root->data) ){
        return root;
    }
    else if(v1<root->data && v2<root->data){
        return lca(root->left, v1, v2);            
    }
    else {
        return lca(root->right, v1, v2);            
    }
}

