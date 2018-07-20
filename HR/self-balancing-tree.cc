// https://www.hackerrank.com/challenges/self-balancing-tree/problem
// Accepted, no consult to discussion


/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */


int height(node *n){
    return n ? n->ht : -1;
}

void fix_ht(node *n){
    if (!n) return;
    int hl = n->left ? height(n->left) + 1 : 0;
    int hr = n->right ? height(n->right) + 1 : 0;
    n->ht = hl>hr ? hl : hr; 
}

int bal(node *node){
    if(!node)
        return 0;
    int hl = height(node->left);
    int hr = height(node->right);
    return hl-hr; 
}

node *create_node(int val){
    node *new_node = new node;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->ht = 0;
    return new_node;
}

node * insert(node * root, int val)
{
    node *new_node = create_node(val);
    if(root == NULL){
       return new_node; 
    } 
              
    val < root->val ? root->left = insert(root->left, val) : root->right = insert(root->right, val);
    fix_ht(root); 
    
    node *new_root = root; 
    // left - right 
    if ( bal(root) == 2 && bal(root->left) == -1){
        
       node *old_left = root->left;
       node *b = root->left->right->left;
       root->left = root->left->right;
       root->left->left = old_left;
       old_left->right = b;
        
       fix_ht(root->left->left);
       fix_ht(root->left);
       fix_ht(root);
    } 
    // left - left  
    if (bal(root) == 2 && bal(root->left) == 1){
        node *c = root->left->right;
        new_root = root->left;
        new_root->right = root;
        new_root->right->left = c; 
       
       fix_ht(new_root->left);
       fix_ht(new_root->right);
       fix_ht(new_root);
    }
    // right - left
    if( bal(root) == -2 && bal(root->right) == 1){
       node *old_right = root->right;
       node *c = root->right->left->right;
       root->right = root->right->left;
       root->right->right = old_right;
       old_right->left = c;
       
       fix_ht(root->right->right);
       fix_ht(root->right);
       fix_ht(root);
    }
    // right - right 
    if( bal(root) == -2 && bal(root->right) == -1){
        node *b = root->right->left;
        new_root = root->right;
        new_root->left = root;
        new_root->left->right = b;
         
       fix_ht(new_root->left);
       fix_ht(new_root->right);
       fix_ht(new_root);
    }
    return new_root; 
}
