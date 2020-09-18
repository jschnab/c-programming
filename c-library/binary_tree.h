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
    char type;
    struct node *left;
    struct node *right;
} BSTNode;


typedef struct bst {
    BSTNode *head;
    int n;
} BST;


int bst_compare_nodes(BSTNode *, BSTNode *);
BSTNode *bst_create_node(void *, char);
BST *bst_init();
