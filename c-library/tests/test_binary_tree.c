#include "../binary_tree.h"


static int n_fail;


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


void test_bst_init_1() {
    BST *tree = bst_init();
    if (tree->n != 0 || tree->head != NULL) {
        printf("test_binary_tree_init: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_binary_tree_init: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for binary search trees...\n\n");
    test_bst_create_node_1();
    test_bst_create_node_2();
    test_bst_create_node_3();
    test_bst_init_1();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
