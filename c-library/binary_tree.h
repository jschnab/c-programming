#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum DATA_TYPES {
    INT    = 1,
    FLOAT  = 2,
    STRING = 3,
};


typedef struct node {
    void *val;
    struct node *left;
    struct node *right;
} BSTNode;


typedef struct bst {
    BSTNode *head;
    char type;
    int n;
} BST;


void bst_add_node(BSTNode *, BSTNode *, char);
int bst_compare_nodes(BSTNode *, BSTNode *, char);
BSTNode *bst_create_node(void *, char);
BST *bst_init(char);
void bst_insert(BST *, void *);
void bst_print_inorder(BST *);
void bst_print_inorder_helper(BSTNode *, char);
void bst_print_preorder(BST *);
void bst_print_preorder_helper(BSTNode *, char);
void bst_print_postorder(BST *);
void bst_print_postorder_helper(BSTNode *, char);
void bst_print_val(void *, char);
