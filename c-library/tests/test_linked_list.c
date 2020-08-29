#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linked_list.h"


static int n_fail = 0;


/* append float to list of length 1 */
void test_list_append_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1, 2};
    head->val = &values[0];
    head->type = FLOAT;
    list_append(head, &values[1], FLOAT);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_append_4: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_append_4: PASS\n");
}


/* append int to list of length 1 */
void test_list_append_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    int values[2] = {1, 2};
    head->val = &values[0];
    head->type = INT;
    list_append(head, &values[1], INT);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || *(int *)head->val != i || head->type != INT) {
            printf("test_list_append_5: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_append_5: PASS\n");
}


/* append string to list of length 1 */
void test_list_append_3() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    char *values[] = {"hello", "world"};
    head->val = values[0];
    head->type = STRING;
    list_append(head, values[1], STRING);
    for (int i = 0; head != NULL; i++) {
        if (i > 1 || strcmp(head->val, values[i]) != 0 || head->type != STRING) {
            printf("test_list_append_6: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_append_6: PASS\n");
}


/* copy an empty list (NULL pointer) */
void test_list_copy_1() {
    ListNode *head = NULL;
    ListNode *copy = list_copy(head);
    if (copy != NULL) {
        printf("test_list_copy_1: FAILED\n");
        n_fail++;
    }
    else
        printf("test_list_copy_1: PASS\n");
}


/* copy a list */
void test_list_copy_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1.0, 2.0};
    head->val = &values[0];
    head->type = FLOAT;
    head->next = node1;
    node1->val = &values[1];
    node1->type = FLOAT;
    ListNode *copy = list_copy(head);
    for (float i = 1.0; copy != NULL; i++) {
        if (i > 2.0 || *(float *)copy->val != i || copy->type != head->type) {
            printf("test_list_copy_2: FAILED\n");
            n_fail++;
            return;
        }
        copy = copy->next;
        head = head->next;
    }
    printf("test_list_copy_2: PASS\n");
}


/* delete middle node */
void test_list_delete_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    float values[] = {1, 3, 2};
    head->val = &values[0];
    head->type = FLOAT;
    node1->val = &values[1];
    node1->type = FLOAT;
    node2->val = &values[2];
    node2->type = FLOAT;
    list_delete(head, 1);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
            printf("test_list_delete_1: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_delete_1: PASS\n");
}


/* delete first node */
void test_list_delete_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    float values[] = {0, 1, 2};
    head->val = &values[0];
    head->type = FLOAT;
    node1->val = &values[1];
    node1->type = FLOAT;
    node2->val = &values[2];
    node2->type = FLOAT;
    list_delete(head, 0);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
            printf("test_list_delete_2: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_delete_2: PASS\n");
}


/* delete last node */
void test_list_delete_3() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    float values[] = {1, 2, 3};
    head->val = &values[0];
    head->type = FLOAT;
    node1->val = &values[1];
    node1->type = FLOAT;
    node2->val = &values[2];
    node2->type = FLOAT;
    list_delete(head, 2);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
            printf("test_list_delete_3: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_delete_3: PASS\n");
}


/* trying to delete node after last node */
void test_list_delete_4() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    float values[] = {1, 2, 3};
    head->val = &values[0];
    head->type = FLOAT;
    node1->val = &values[1];
    node1->type = FLOAT;
    node2->val = &values[2];
    node2->type = FLOAT;
    list_delete(head, 3);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 3.0 || *(float *)head->val != i) {
            printf("test_list_delete_4: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_delete_4: PASS\n");
}


/* compare same lists */
void test_list_equal_1() {
    ListNode *A = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A2 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B2 = (ListNode *) malloc(sizeof(ListNode));
    int values[] = {1, 2, 3};
    A->val = B->val = &values[0];
    A1->val = B1->val = &values[1];
    A2->val = B2->val = &values[2];
    A->type = A1->type = A2->type = INT;
    B->type = B1->type = B2->type = INT;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    B1->next = B2;
    if (list_equal(A, B) == 1)
        printf("test_list_equal_1: PASS\n");
    else {
        printf("test_list_equal_1: FAILED\n");
        n_fail++;
    }
}


/* compare lists with same nodes but different length */
void test_list_equal_2() {
    ListNode *A = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A2 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B1 = (ListNode *) malloc(sizeof(ListNode));
    int values[] = {1, 2, 3};
    A->val = B->val = &values[0];
    A1->val = B1->val = &values[1];
    A2->val = &values[2];
    A->type = A1->type = A2->type = INT;
    B->type = B1->type = INT;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    if (list_equal(A, B) == 0)
        printf("test_list_equal_2: PASS\n");
    else {
        printf("test_list_equal_2: FAILED\n");
        n_fail++;
    }
}


/* compare lists with different nodes */
void test_list_equal_3() {
    ListNode *A = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A2 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B2 = (ListNode *) malloc(sizeof(ListNode));
    int values[] = {1, 2, 3, 4};
    A->val = B->val = &values[0];
    A1->val = B1->val = &values[1];
    A2->val = &values[2];
    B2->val = &values[3];
    A->type = A1->type = A2->type = INT;
    B->type = B1->type = B2->type = INT;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    B1->next = B2;
    if (list_equal(A, B) == 0)
        printf("test_list_equal_3: PASS\n");
    else {
        printf("test_list_equal_3: FAILED\n");
        n_fail++;
    }
}


/* trying to insert node in empty list (NULL pointer) */
void test_list_insert_1() {
    ListNode *head = NULL;
    int val = 1;
    list_insert(head, &val, INT, 1);
    if (head == NULL)
        printf("test_list_insert_1: PASS\n");
    else {
        printf("test_list_insert_1: FAILED\n");
        n_fail++;
    }
}


/* trying to insert node at index 0 */
void test_list_insert_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1.0, 2.0};
    head->val = &values[0];
    list_insert(head, &values[1], FLOAT, 0);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 1.0 || *(float *)head->val != i) {
            printf("test_list_insert_2: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_2: PASS\n");
}


/* insert node in middle of list */
void test_list_insert_3() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1.0, 2.0, 3.0};
    head->val = &values[0];
    head->type = FLOAT;
    head->next = node1;
    node1->val = &values[2];
    node1->type = FLOAT;
    list_insert(head, &values[1], FLOAT, 1);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 3.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_insert_3: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_3: PASS\n");
}


/* insert float node at front of list */
void test_list_insert_front_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1.0, 2.0};
    head->val = &values[1];
    head->type = FLOAT;
    list_insert_front(&head, &values[0], FLOAT);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_insert_front_1: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_1: PASS\n");
}


/* insert float node at front of empty list (NULL pointer) */
void test_list_insert_front_2() {
    ListNode *head = NULL;
    float value = 1.0;
    list_insert_front(&head, &value, FLOAT);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 1.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_insert_front_2: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_2: PASS\n");
}


/* insert int node at from of list */
void test_list_insert_front_3() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    int values[] = {1, 2};
    head->val = &values[1];
    head->type = INT;
    list_insert_front(&head, &values[0], INT);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || *(int *)head->val != i || head->type != INT) {
            printf("test_list_insert_front_3: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_3: PASS\n");
}


/* insert int node at front of empty list (NULL pointer) */
void test_list_insert_front_4() {
    ListNode *head = NULL;
    int value = 1;
    list_insert_front(&head, &value, INT);
    for (int i = 1; head != NULL; i++) {
        if (i > 1 || *(int *)head->val != i || head->type != INT) {
            printf("test_list_insert_front_4: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_4: PASS\n");
}


/* insert string node at from of list */
void test_list_insert_front_5() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    char *values[] = {"hello", "world"};
    head->val = values[1];
    head->type = STRING;
    list_insert_front(&head, values[0], STRING);
    for (int i = 0; head != NULL; i++) {
        if (i > 1 || strcmp((char *)head->val, values[i]) != 0 || head->type != STRING) {
            printf("test_list_insert_front_5: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_5: PASS\n");
}


/* insert int node at front of empty list (NULL pointer) */
void test_list_insert_front_6() {
    ListNode *head = NULL;
    char *values[] = {"hello"};
    list_insert_front(&head, values[0], STRING);
    for (int i = 0; head != NULL; i++) {
        if (i > 0 || strcmp((char *)head->val, values[i]) != 0 || head->type != STRING) {
            printf("test_list_insert_front_6: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_6: PASS\n");
}


/* length of list containing 1 node */
void test_list_length_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    if (list_length(head) != 1) {
        printf("test_list_length_1: FAILED\n");
        n_fail++;
    }
    else
        printf("test_list_length_1: PASS\n");
}


/* length of empty list (NULL pointer) */
void test_list_length_2() {
    ListNode *head = NULL;
    if (list_length(head) != 0) {
        printf("test_list_length_2: FAILED\n");
        n_fail++;
    }
    else
        printf("test_list_length_2: PASS\n");
}


/* reverse list */
void test_list_reverse_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1.0, 2.0};
    head->val = &values[0];
    head->type = FLOAT;
    head->next = node1;
    node1->val = &values[1];
    node1->type = FLOAT;
    list_reverse(&head);
    for (float i = 2.0; head != NULL; i--) {
        if (i < 1.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_reverse_1: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_reverse_1: PASS\n");
}


/* reverse an empty list (NULL pointer) */
void test_list_reverse_2() {
    ListNode *head = NULL;
    list_reverse(&head);
    if (head != NULL) {
        printf("test_list_reverse_2: FAILED\n");
        n_fail++;
    }
    else
        printf("test_list_reverse_2: PASS\n");
}


/* trying to convert empty list (NULL pointer) to array */
void test_list_to_array_1() {
    ListNode *head = NULL;
    float array[1] = {-999.0};  /* sentinel value: not expected to change */
    list_to_array(head, array, FLOAT);
    if (array[0] != -999.0) {
        printf("test_list_to_array_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_list_to_array_1: PASS\n");
}


/* convert list containing 3 float nodes to array */
void test_list_to_array_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    float values[] = {1.0, 2.0, 3.0};
    head->val = &values[0];
    node1->val = &values[1];
    node2->val = &values[2];
    head->type = node1->type = node2->type = FLOAT;
    float array[3];
    list_to_array(head, array, FLOAT);
    for (int i = 1; i <= 3; i++) {
        if (array[i-1] != (float)i) {
            printf("test_list_to_array_2: FAILED\n");
            n_fail++;
            return;
        }
    }
    printf("test_list_to_array_2: PASS\n");
}


/* convert list containing 3 integer nodes to array */
void test_list_to_array_3() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    int values[] = {1, 2, 3};
    head->val = &values[0];
    node1->val = &values[1];
    node2->val = &values[2];
    head->type = node1->type = node2->type = INT;
    int array[3];
    list_to_array(head, array, INT);
    for (int i = 1; i <= 3; i++) {
        if (array[i-1] != i) {
            printf("test_list_to_array_3: FAILED\n");
            n_fail++;
            return;
        }
    }
    printf("test_list_to_array_3: PASS\n");
}


/* convert list containing 3 string nodes to array */
void test_list_to_strarray_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    char *values[] = {"brave", "new", "world"};
    head->val = values[0];
    node1->val = values[1];
    node2->val = values[2];
    head->type = node1->type = node2->type = STRING;
    char *array[3];
    list_to_strarray(head, array);
    for (int i = 0; i < 3; i++) {
        if (strcmp(array[i], values[i]) != 0) {
            printf("test_list_to_strarray_1: FAILED\n");
            n_fail++;
            return;
        }
    }
    printf("test_list_to_array_1: PASS\n");
}


/* make a integer list from a sequence of numbers */
void test_list_from_args_1() {
    ListNode *head = list_from_args(3, INT, 1, 2, 3);
    for (int i = 1; head != NULL; i++) {
        if (i > 3 || *(int *)head->val != i || head->type != INT) {
            printf("test_list_from_args_1: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_from_args_1: PASS\n");
}


/* make a float list from a sequence of numbers */
void test_list_from_args_2() {
    ListNode *head = list_from_args(3, FLOAT, 1.0, 2.0, 3.0);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 3.0 || *(float *)head->val != i || head->type != FLOAT) {
            printf("test_list_from_args_2: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_from_args_2: PASS\n");
}


/* make a string list from a sequence of words */
void test_list_from_args_3() {
    char *words[] = {"brave", "new", "world"};
    ListNode *head = list_from_args(3, STRING, "brave", "new", "world");
    for (int i = 0; head != NULL; i++) {
        if (i > 2 || strcmp((char *)head->val, words[i]) != 0 || head->type != STRING) {
            printf("test_list_from_args_3: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    printf("test_list_from_args_3: PASS\n");
}


void test_list_print() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    char *s1 = "hello";
    char *s2 = "world";
    head->val = s1;
    head->type = STRING;
    head->next = node1;
    node1->val = s2;
    node1->type = STRING;
    list_print(head);
}


int main(int argc, char *argv[]) {
    printf("Running tests on linked lists functions...\n\n");
    test_list_append_1();
    test_list_append_2();
    test_list_append_3();
    test_list_copy_1();
    test_list_copy_2();
    test_list_delete_1();
    test_list_delete_2();
    test_list_delete_3();
    test_list_delete_4();
    test_list_equal_1();
    test_list_equal_2();
    test_list_equal_3();
    test_list_from_args_1();
    test_list_from_args_2();
    test_list_from_args_3();
    test_list_insert_1();
    test_list_insert_2();
    test_list_insert_3();
    test_list_insert_front_1();
    test_list_insert_front_2();
    test_list_insert_front_3();
    test_list_insert_front_4();
    test_list_insert_front_5();
    test_list_insert_front_6();
    test_list_length_1();
    test_list_length_2();
    test_list_reverse_1();
    test_list_reverse_2();
    test_list_to_array_1();
    test_list_to_array_2();
    test_list_to_array_3();
    test_list_to_strarray_1();
    printf("\nTests finished.\nNumber of failures: %d\n", n_fail);
    return 0;
}
