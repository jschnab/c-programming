#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"

#define max(a, b) (a > b ? a : b)


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
int bst_compare_node_value(BSTNode *, void *, char);
BSTNode *bst_create_node(void *, char);
void bst_delete(BST *, void *);
BSTNode *bst_delete_helper(BSTNode *, void *, char);
BST *bst_from_array(void *, char, int);
int bst_height(BST *);
int bst_height_helper(BSTNode *);
BST *bst_init(char);
void bst_insert(BST *, void *);
void bst_print_inorder(BST *);
void bst_print_inorder_helper(BSTNode *, char);
void bst_print_preorder(BST *);
void bst_print_preorder_helper(BSTNode *, char);
void bst_print_postorder(BST *);
void bst_print_postorder_helper(BSTNode *, char);
void bst_print_val(void *, char);
BSTNode *bst_rightmost(BSTNode *);
void bst_to_array(BST *, void *);

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


/* compare the value of a node with the value from a pointer, returns an integer:
 *  0 if the values are equal
 *  1 if the value of A > B
 * -1 if the value of A < B */
int bst_compare_node_value(BSTNode *node, void *value, char type) {
    int i1, i2;
    float f1, f2;
    char *s1, *s2;
    switch (type) {
        case INT:
            i1 = *(int *)node->val;
            i2 = *(int *)value;
            if (i1 < i2)
                return -1;
            if (i1 > i2)
                return 1;
            return 0;
        case FLOAT:
            f1 = *(float *)node->val;
            f2 = *(float *)value;
            if (f1 < f2)
                return -1;
            if (f1 > f2)
                return 1;
            return 0;
        case STRING:
            s1 = (char *)node->val;
            s2 = (char *)value;
            return strcmp(s1, s2);
        default:
            printf("error: node type not supported\n");
            exit(1);
    }
}


/* make a BST from an array, given its type and length n */
BST *bst_from_array(void *array, char type, int n) {
    BST *tree = bst_init(type);
    for (int i = 0; i < n; i++) {
        switch (type) {
            case INT:
                bst_insert(tree, &((int *)array)[i]);
                break;
            case FLOAT:
                bst_insert(tree, &((float *)array)[i]);
                break;
            case STRING:
                bst_insert(tree, ((char **)array)[i]);
                break;
        }
    }
    return tree;
}


/* delete a node from the tree given its value
 * assuming only one node in the tree has this value */
void bst_delete(BST *tree, void *value) {
    if (tree->head != NULL) {
        tree->head = bst_delete_helper(tree->head, value, tree->type);
        tree->n--;
    }
}


/* helper function for the bst_delete() function */
BSTNode *bst_delete_helper(BSTNode *root, void *value, char type) {
    if (root == NULL)
        return NULL;

    /* node has no children */
    if (
        bst_compare_node_value(root, value, type) == 0 &&
        root->left == NULL &&
        root->right == NULL
    ) {
        free(root);
        return NULL;
    }

    /* node has a single left child */
    if (
        bst_compare_node_value(root, value, type) == 0 &&
        root->left != NULL &&
        root->right == NULL
    )
        return root->left;

    /* node has a single right child */
    if (
        bst_compare_node_value(root, value, type) == 0 &&
        root->left == NULL &&
        root->right != NULL
    )
        return root->right;

    /* node has both children */
    if (
        bst_compare_node_value(root, value, type) == 0 &&
        root->left != NULL &&
        root->right != NULL
    ) {
        BSTNode *rightmost = bst_rightmost(root->left);
        switch (type) {
            case INT:
                memcpy(root->val, rightmost->val, sizeof(int));
                break;
            case FLOAT:
                memcpy(root->val, rightmost->val, sizeof(float));
                break;
            case STRING:
                memcpy(root->val, rightmost->val, strlen(value));
                break;
            default:
                printf("error: node value not supported\n");
                exit(1);
        }
        root->left = bst_delete_helper(root->left, rightmost->val, type);
    }

    /* recursively traverse the tree to find the value to delete */
    if (bst_compare_node_value(root, value, type) > 0)
        root->left = bst_delete_helper(root->left, value, type);
    else if (bst_compare_node_value(root, value, type) < 0)
        root->right = bst_delete_helper(root->right, value, type);

    return root;
}


/* get the height of the tree */
int bst_height(BST *tree) {
    return bst_height_helper(tree->head);
}


/* helper function for the `bst_height()` function */
int bst_height_helper(BSTNode *node) {
    if (node == NULL)
        return 0;
    int left = bst_height_helper(node->left);
    int right = bst_height_helper(node->right);
    return 1 + max(left, right);
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
    if (tree->head != NULL)
        bst_add_node(tree->head, new, tree->type);
    else
        tree->head = new;
    tree->n++;
}


/* print the list of tree nodes with inorder traversal */
void bst_print_inorder(BST *tree) {
    printf("[ ");
    if (tree->head != NULL)
        bst_print_inorder_helper(tree->head, tree->type);
    printf("]\n");
}


/* help print the list or tree nodes with inorder traversal */
void bst_print_inorder_helper(BSTNode *head, char type) {
    if (head->left != NULL)
        bst_print_inorder_helper(head->left, type);
    bst_print_val(head->val, type);
    if (head->right != NULL)
        bst_print_inorder_helper(head->right, type);
}


/* print the list of tree nodes with preorder traversal */
void bst_print_preorder(BST *tree) {
    printf("[ ");
    if (tree->head != NULL)
        bst_print_preorder_helper(tree->head, tree->type);
    printf("]\n");
}


/* help print the list or tree nodes with preorder traversal */
void bst_print_preorder_helper(BSTNode *head, char type) {
    bst_print_val(head->val, type);
    if (head->left != NULL)
        bst_print_preorder_helper(head->left, type);
    if (head->right != NULL)
        bst_print_preorder_helper(head->right, type);
}


/* print the list of tree nodes with postorder traversal */
void bst_print_postorder(BST *tree) {
    printf("[ ");
    if (tree->head != NULL)
        bst_print_postorder_helper(tree->head, tree->type);
    printf("]\n");
}


/* help print the list or tree nodes with postorder traversal */
void bst_print_postorder_helper(BSTNode *head, char type) {
    if (head->left != NULL)
        bst_print_postorder_helper(head->left, type);
    if (head->right != NULL)
        bst_print_postorder_helper(head->right, type);
    bst_print_val(head->val, type);
}


/* help print node value with the correct format */
void bst_print_val(void *val, char type) {
    switch (type) {
        case INT:
            printf("%d, ", *(int *)val);
            break;
        case FLOAT:
            printf("%f, ", *(float *)val);
            break;
        case STRING:
            printf("%s, ", (char *)val);
        default:
            printf("?, ");
    }
}


/* get rightmost node of a node */
BSTNode *bst_rightmost(BSTNode *node) {
    if (node->right == NULL)
        return node;
    return bst_rightmost(node->right);
}


/* populate a given array with node values from a tree
 * we use the Morris algorithm, iterative and uses no stack */
void bst_to_array(BST *tree, void *array) {
    BSTNode *node = tree->head;
    BSTNode *predecessor;

    while (node != NULL) {

        if (node->left != NULL) {
            predecessor = node->left;

            while (predecessor->right != NULL && predecessor->right != node)
                predecessor = predecessor->right;

            if (predecessor->right == NULL) {
                predecessor->right = node;
                node = node->left;
            }
            else {
                switch (tree->type) {
                    case INT:
                        *(int *)array = *(int *)node->val;
                        array += sizeof(int);
                        break;
                    case FLOAT:
                        *(float *)array = *(float *)node->val;
                        array += sizeof(float);
                        break;
                }
                predecessor->right = NULL;
                node = node->right;
            }

        }
        else {
            switch (tree->type) {
                case INT:
                    *(int *)array = *(int *)node->val;
                    array += sizeof(int);
                    break;
                case FLOAT:
                    *(float *)array = *(float *)node->val;
                    array += sizeof(float);
                    break;
            }
            node = node->right;
        }
    }
}
