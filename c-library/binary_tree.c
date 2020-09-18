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


/* recursively add a new node to the left or right of an existing node
 * given its type and value */
void bst_add_node(BSTNode *node, BSTNode *new, char type) {
    if (bst_compare_nodes(new, node, type) <= 0) {
        if (node->left == NULL)
            node->left = new;
        else
            bst_add_node(node->left, new, type);
    }
    else {
        if (node->right == NULL)
            node->right = new;
        else
            bst_add_node(node->right, new, type);
    }
}


/* compare the value of two BST nodes, returns an integer:
 *  0 if the values are equal
 *  1 if the value of A > B
 * -1 if the value of A < B
 * Important: this function assumes nodes have the same type */
int bst_compare_nodes(BSTNode *a, BSTNode *b, char type) {
    int i1, i2;
    float f1, f2;
    char *s1, *s2;
    switch (type) {
        case INT:
            i1 = *(int *)a->val;
            i2 = *(int *)b->val;
            if (i1 < i2)
                return -1;
            else if (i1 > i2)
                return 1;
            else
                return 0;
        case FLOAT:
            f1 = *(float *)a->val;
            f2 = *(float *)b->val;
            if (f1 < f2)
                return -1;
            else if (f1 > f2)
                return 1;
            else
                return 0;
        case STRING:
            s1 = (char *)a->val;
            s2 = (char *)b->val;
            return strcmp(s1, s2);
        default:
            printf("error: node type not supported\n");
            exit(1);
    }
}


/* initialize an empty binary search tree */
BST *bst_init(char type) {
    BST *tree = (BST *) malloc(sizeof(BST));
    if (tree == NULL) {
        printf("error: malloc failed when initializing BST\n");
        exit(1);
    }
    tree->type = type;
    tree->head = NULL;
    tree->n = 0;
    return tree;
}


/* create a node with the given value and type */
BSTNode *bst_create_node(void *val, char type) {
    BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
    if (node == NULL) {
        printf("error: malloc failed when initializing BSTNode\n");
        exit(1);
    }
    switch (type) {
        case INT:
            node->val = (int *) malloc(sizeof(int));
            if (node->val == NULL) {
                printf("error: malloc failed when initializing BSTNode\n");
                exit(1);
            }
            memcpy(node->val, val, sizeof(int));
            break;
        case FLOAT:
            node->val = (float *) malloc(sizeof(float));
            if (node->val == NULL) {
                printf("error: malloc failed when initializing BSTNode\n");
                exit(1);
            }
            memcpy(node->val, val, sizeof(float));
            break;
        case STRING:
            node->val = (char *) malloc(strlen(val));
            if (node->val == NULL) {
                printf("error: malloc failed when initializing BSTNode\n");
                exit(1);
            }
            memcpy(node->val, val, strlen(val));
            break;
    }
    node->left = NULL;
    node->right = NULL;
    return node;
}


/* insert a new value into the tree */
void bst_insert(BST *tree, void *val) {
    BSTNode *new = bst_create_node(val, tree->type);
    bst_add_node(tree->head, new, tree->type);
}