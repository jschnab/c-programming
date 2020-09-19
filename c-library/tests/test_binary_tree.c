#include "../binary_tree.h"


static int n_fail;


/* add node to the left of another node (node < other)
 * base case */
void test_bst_add_node_1() {
    int i = 3;
    int j = 2;
    BSTNode *head = bst_create_node(&i, INT);
    BSTNode *new = bst_create_node(&j, INT);
    bst_add_node(head, new, INT);
    if (
        *(int *)head->val != i ||
        head->right != NULL ||
        *(int *)head->left->val != j
    ) {
        printf("test_bst_add_node_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_add_node_1: PASS\n");
}


/* add node to the left of another node (node == other)
 * base case */
void test_bst_add_node_2() {
    int i = 7;
    int j = 7;
    BSTNode *head = bst_create_node(&i, INT);
    BSTNode *new = bst_create_node(&j, INT);
    bst_add_node(head, new, INT);
    if (
        *(int *)head->val != i ||
        head->right != NULL ||
        *(int *)head->left->val != j
    ) {
        printf("test_bst_add_node_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_add_node_2: PASS\n");
}


/* add node to the right of another node (node > other)
 * base case */
void test_bst_add_node_3() {
    int i = 7;
    int j = 11;
    BSTNode *head = bst_create_node(&i, INT);
    BSTNode *new = bst_create_node(&j, INT);
    bst_add_node(head, new, INT);
    if (
        *(int *)head->val != i ||
        head->left != NULL ||
        *(int *)head->right->val != j
    ) {
        printf("test_bst_add_node_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_add_node_3: PASS\n");
}


/* add node to the left of another node (node < other)
 * recursive case */
void test_bst_add_node_4() {
    int i = 5;
    int j = 9;
    int k = 8;
    BSTNode *head = bst_create_node(&i, INT);
    BSTNode *right = bst_create_node(&j, INT);
    BSTNode *new = bst_create_node(&k, INT);
    bst_add_node(head, right, INT);
    bst_add_node(head, new, INT);
    if (
        *(int *)head->val != i ||
        head->left != NULL ||
        *(int *)head->right->val != j ||
        head->right->right != NULL ||
        *(int *)head->right->left->val != k
    ) {
        printf("test_bst_add_node_4: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_add_node_4: PASS\n");
}


/* add node to the right of another node (node > other)
 * recursive case */
void test_bst_add_node_5() {
    int i = 5;
    int j = 0;
    int k = 3;
    BSTNode *head = bst_create_node(&i, INT);
    BSTNode *left = bst_create_node(&j, INT);
    BSTNode *new = bst_create_node(&k, INT);
    bst_add_node(head, left, INT);
    bst_add_node(head, new, INT);
    if (
        *(int *)head->val != i ||
        head->right != NULL ||
        *(int *)head->left->val != j ||
        head->left->left != NULL ||
        *(int *)head->left->right->val != k
    ) {
        printf("test_bst_add_node_5: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_add_node_5: PASS\n");
}


/* compare two different integer nodes
 * node 'a' is lesser than node 'b' */
void test_bst_compare_nodes_1() {
    int i = 1;
    int j = 3;
    BSTNode *a = bst_create_node(&i, INT);
    BSTNode *b = bst_create_node(&j, INT);
    if (bst_compare_nodes(a, b, INT) != -1) {
        printf("test_bst_compare_nodes_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_1: PASS\n");
}


/* compare two different integer nodes
 * node 'a' equal to node 'b' */
void test_bst_compare_nodes_2() {
    int i = 4;
    int j = 4;
    BSTNode *a = bst_create_node(&i, INT);
    BSTNode *b = bst_create_node(&j, INT);
    if (bst_compare_nodes(a, b, INT) != 0) {
        printf("test_bst_compare_nodes_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_2: PASS\n");
}


/* compare two different integer nodes
 * node 'a' greater than node 'b' */
void test_bst_compare_nodes_3() {
    int i = 6;
    int j = 5;
    BSTNode *a = bst_create_node(&i, INT);
    BSTNode *b = bst_create_node(&j, INT);
    if (bst_compare_nodes(a, b, INT) != 1) {
        printf("test_bst_compare_nodes_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_3: PASS\n");
}


/* compare two different float nodes
 * node 'a' is lesser than node 'b' */
void test_bst_compare_nodes_4() {
    float i = 1.0;
    float j = 3.0;
    BSTNode *a = bst_create_node(&i, FLOAT);
    BSTNode *b = bst_create_node(&j, FLOAT);
    if (bst_compare_nodes(a, b, FLOAT) != -1) {
        printf("test_bst_compare_nodes_4: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_4: PASS\n");
}


/* compare two different float nodes
 * node 'a' equal to node 'b' */
void test_bst_compare_nodes_5() {
    float i = 4.0;
    float j = 4.0;
    BSTNode *a = bst_create_node(&i, FLOAT);
    BSTNode *b = bst_create_node(&j, FLOAT);
    if (bst_compare_nodes(a, b, FLOAT) != 0) {
        printf("test_bst_compare_nodes_5: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_5: PASS\n");
}


/* compare two different float nodes
 * node 'a' greater than node 'b' */
void test_bst_compare_nodes_6() {
    float i = 6.0;
    float j = 5.0;
    BSTNode *a = bst_create_node(&i, FLOAT);
    BSTNode *b = bst_create_node(&j, FLOAT);
    if (bst_compare_nodes(a, b, FLOAT) != 1) {
        printf("test_bst_compare_nodes_6: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_6: PASS\n");
}


/* compare two different string nodes
 * node 'a' is lesser than node 'b' */
void test_bst_compare_nodes_7() {
    char *i = "hello";
    char *j = "world";
    BSTNode *a = bst_create_node(i, STRING);
    BSTNode *b = bst_create_node(j, STRING);
    if (bst_compare_nodes(a, b, STRING) >= 0) {
        printf("test_bst_compare_nodes_7: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_7: PASS\n");
}


/* compare two different string nodes
 * node 'a' equal to node 'b' */
void test_bst_compare_nodes_8() {
    char *i = "hello";
    char *j = "hello";
    BSTNode *a = bst_create_node(i, STRING);
    BSTNode *b = bst_create_node(j, STRING);
    if (bst_compare_nodes(a, b, STRING) != 0) {
        printf("test_bst_compare_nodes_8: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_8: PASS\n");
}


/* compare two different string nodes
 * node 'a' greater than node 'b' */
void test_bst_compare_nodes_9() {
    char *i = "world";
    char *j = "hello";
    BSTNode *a = bst_create_node(i, STRING);
    BSTNode *b = bst_create_node(j, STRING);
    if (bst_compare_nodes(a, b, STRING) <= 0) {
        printf("test_bst_compare_nodes_9: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_compare_nodes_9: PASS\n");
}


/* create an integer node */
void test_bst_create_node_1() {
    int value = 5;
    BSTNode *node = bst_create_node(&value, INT);
    if (*(int *)node->val != value || node->left != NULL || node->right != NULL) {
        printf("test_bst_create_node_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_create_node_1: PASS\n");
}


/* create an float node */
void test_bst_create_node_2() {
    float value = 9;
    BSTNode *node = bst_create_node(&value, FLOAT);
    if (*(float *)node->val != value || node->left != NULL || node->right != NULL) {
        printf("test_bst_create_node_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_create_node_2: PASS\n");
}

/* create an string node */
void test_bst_create_node_3() {
    char *value = "hello";
    BSTNode *node = bst_create_node(value, STRING);
    if (
        strcmp((char *)node->val, value) != 0 ||
        node->left != NULL ||
        node->right != NULL
    ) {
        printf("test_bst_create_node_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_create_node_3: PASS\n");
}


/* initialize a tree of integers */
void test_bst_init_1() {
    char type = INT;
    BST *tree = bst_init(type);
    if (tree->n != 0 || tree->head != NULL || tree->type != type) {
        printf("test_bst_init_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_init_1: PASS\n");
}


/* initialize a tree of floats */
void test_bst_init_2() {
    char type = FLOAT;
    BST *tree = bst_init(type);
    if (tree->n != 0 || tree->head != NULL || tree->type != type) {
        printf("test_bst_init_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_init_2: PASS\n");
}


/* initialize a tree of strings */
void test_bst_init_3() {
    char type = STRING;
    BST *tree = bst_init(type);
    if (tree->n != 0 || tree->head != NULL || tree->type != type) {
        printf("test_bst_init_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_bst_init_3: PASS\n");
}


/* print integer BST, inorder traversal */
void test_bst_print_inorder_1() {
    int values[] = {10, 4, 11, 1, 22, 5, 16};
    BST *tree = bst_init(INT);
    for (int i = 0; i < 7; i++) {
        bst_insert(tree, &values[i]);
    }
    bst_print_inorder(tree);
}


/* print integer BST, preorder traversal */
void test_bst_print_preorder_1() {
    int values[] = {10, 4, 11, 1, 22, 5, 16};
    BST *tree = bst_init(INT);
    for (int i = 0; i < 7; i++) {
        bst_insert(tree, &values[i]);
    }
    bst_print_preorder(tree);
}


/* print integer BST, postorder traversal */
void test_bst_print_postorder_1() {
    int values[] = {10, 4, 11, 1, 22, 5, 16};
    BST *tree = bst_init(INT);
    for (int i = 0; i < 7; i++) {
        bst_insert(tree, &values[i]);
    }
    bst_print_postorder(tree);
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for binary search trees...\n\n");
    test_bst_add_node_1();
    test_bst_add_node_2();
    test_bst_add_node_3();
    test_bst_add_node_4();
    test_bst_add_node_5();
    test_bst_compare_nodes_1();
    test_bst_compare_nodes_2();
    test_bst_compare_nodes_3();
    test_bst_compare_nodes_4();
    test_bst_compare_nodes_5();
    test_bst_compare_nodes_6();
    test_bst_compare_nodes_7();
    test_bst_compare_nodes_8();
    test_bst_compare_nodes_9();
    test_bst_create_node_1();
    test_bst_create_node_2();
    test_bst_create_node_3();
    test_bst_init_1();
    test_bst_init_2();
    test_bst_init_3();
    test_bst_print_inorder_1();
    test_bst_print_preorder_1();
    test_bst_print_postorder_1();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
