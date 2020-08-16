#include <stdio.h>
#include <stdlib.h>
#include "../linked_list.h"


/* trying to convert empty list (NULL pointer) to array */
void test_list_to_array_1() {
    ListNode *head = NULL;
    int array[1] = {-999};  /* sentinel value: should not change */
    list_to_array(head, array);
    if (array[0] != -999) {
        printf("test_list_to_array_1: FAILED\n");
        return;
    }
    printf("test_list_to_array_1: PASS\n");
}


/* convert list containing 3 nodes to array */
void test_list_to_array_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    head->val = 1;
    node1->val = 2;
    node2->val = 3;
    int array[3];
    list_to_array(head, array);
    for (int i = 1; i <= 3; i++)
        if (array[i-1] != i) {
            printf("test_list_to_array_2: FAILED\n");
            return;
        }
    printf("test_list_to_array_2: PASS\n");
}


/* length of list containing 1 node */
void test_list_length_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    if (list_length(head) != 1)
        printf("test_list_length_1: FAILED\n");
    else
        printf("test_list_length_1: PASS\n");
}


/* length of empty list (NULL pointer) */
void test_list_length_2() {
    ListNode *head = NULL;
    if (list_length(head) != 0)
        printf("test_list_length_2: FAILED\n");
    else
        printf("test_list_length_2: PASS\n");
}


/* append to list of length 1 */
void test_list_append_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    head->val = 1;
    list_append(head, 2);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || head->val != i) {
            printf("test_list_append_1: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_append_1: PASS\n");
}


/* append to empty list (NULL pointer) */
void test_list_append_2() {
    ListNode *head = NULL;
    list_append(head, 1);
    for (int i = 1; head != NULL; i ++) {
        if (i > 1) {
            printf("test_list_append_2: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_append_2: PASS\n");
}


/* delete middle node */
void test_list_delete_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode *) malloc(sizeof(ListNode));
    head->next = node1;
    node1->next = node2;
    head->val = 1;
    node1->val = 3;
    node2->val = 2;
    list_delete(head, 1);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || head->val != i) {
            printf("test_list_delete_1: FAILED\n");
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
    head->val = 0;
    node1->val = 1;
    node2->val = 2;
    list_delete(head, 0);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || head->val != i) {
            printf("test_list_delete_2: FAILED\n");
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
    head->val = 1;
    node1->val = 2;
    node2->val = 3;
    list_delete(head, 2);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || head->val != i) {
            printf("test_list_delete_3: FAILED\n");
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
    head->val = 1;
    node1->val = 2;
    node2->val = 3;
    list_delete(head, 3);
    for (int i = 1; head != NULL; i++) {
        if (i > 3 || head->val != i) {
            printf("test_list_delete_4: FAILED\n");
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
    A->val = B->val = 1;
    A1->val = B1->val = 2;
    A2->val = B2->val = 3;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    B1->next = B2;
    if (list_equal(A, B) == 1)
        printf("test_list_equal_1: PASS\n");
    else
        printf("test_list_equal_1: FAILED\n");
}


/* compare lists with same nodes but different length */
void test_list_equal_2() {
    ListNode *A = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A2 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B1 = (ListNode *) malloc(sizeof(ListNode));
    A->val = B->val = 1;
    A1->val = B1->val = 2;
    A2->val = 3;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    if (list_equal(A, B) == 0)
        printf("test_list_equal_2: PASS\n");
    else
        printf("test_list_equal_2: FAILED\n");
}


/* compare lists with different nodes */
void test_list_equal_3() {
    ListNode *A = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *A2 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B1 = (ListNode *) malloc(sizeof(ListNode));
    ListNode *B2 = (ListNode *) malloc(sizeof(ListNode));
    A->val = B->val = 1;
    A1->val = B1->val = 2;
    A2->val = 3;
    B2->val = 4;
    A->next = A1;
    A1->next = A2;
    B->next = B1;
    B1->next = B2;
    if (list_equal(A, B) == 0)
        printf("test_list_equal_3: PASS\n");
    else
        printf("test_list_equal_3: FAILED\n");
}


/* trying to insert node in empty list (NULL pointer) */
void test_list_insert_1() {
    ListNode *head = NULL;
    list_insert(head, 1, 1);
    if (head == NULL)
        printf("test_list_insert_1: PASS\n");
    else
        printf("test_list_insert_1: FAILED\n");
}


/* trying to insert node at index 0 */
void test_list_insert_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    head->val = 1;
    list_insert(head, 2, 0);
    for (int i = 1; head != NULL; i++) {
        if (i > 1 || head->val != i) {
            printf("test_list_insert_2: FAILED\n");
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
    head->val = 1;
    head->next = node1;
    node1->val = 3;
    list_insert(head, 2, 1);
    for (int i = 1; head != NULL; i++) {
        if (i > 3 || head->val != i) {
            printf("test_list_insert_3: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_3: PASS\n");
}


/* insert node at front of list */
void test_list_insert_front_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    head->val = 2;
    list_insert_front(&head, 1);
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || head->val != i) {
            printf("test_list_insert_front_1: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_1: PASS\n");
}


/* insert node at front of empty list (NULL pointer) */
void test_list_insert_front_2() {
    ListNode *head = NULL;
    list_insert_front(&head, 1);
    for (int i = 1; head != NULL; i++) {
        if (i > 1 || head->val != i) {
            printf("test_list_insert_front_2: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_insert_front_2: PASS\n");
}


/* reverse list */
void test_list_reverse_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    head->val = 1;
    head->next = node1;
    node1->val = 2;
    list_reverse(&head);
    for (int i = 2; head != NULL; i--) {
        if (i < 1 || head->val != i) {
            printf("test_list_reverse_1: FAILED\n");
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
    if (head != NULL)
        printf("test_list_reverse_2: FAILED\n");
    else
        printf("test_list_reverse_2: PASS\n");
}


/* copy an empty list (NULL pointer) */
void test_list_copy_1() {
    ListNode *head = NULL;
    ListNode *copy = list_copy(head);
    if (copy != NULL)
        printf("test_list_copy_1: FAILED\n");
    else
        printf("test_list_copy_1: PASS\n");
}


/* copy a list */
void test_list_copy_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *node1 = (ListNode *) malloc(sizeof(ListNode));
    head->val = 1;
    head->next = node1;
    node1->val = 2;
    ListNode *copy = list_copy(head);
    for (int i = 1; copy != NULL; i++) {
        if (i > 2 || copy->val != i) {
            printf("test_list_copy_2: FAILED\n");
            return;
        }
        copy = copy->next;
    }
    printf("test_list_copy_2: PASS\n");
}


/* make a list from a sequence of numbers */
void test_list_from_args_1() {
    ListNode *head = list_from_args(3, 1, 2, 3);
    for (int i = 1; head != NULL; i++) {
        if (i > 3 || head->val != i) {
            printf("test_list_from_args_1: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_from_args_1: PASS\n");
}


int main(int argc, char *argv[]) {
    test_list_to_array_1();
    test_list_to_array_2();
    test_list_length_1();
    test_list_length_2();
    test_list_append_1();
    test_list_append_2();
    test_list_delete_1();
    test_list_delete_2();
    test_list_delete_3();
    test_list_delete_4();
    test_list_equal_1();
    test_list_equal_2();
    test_list_equal_3();
    test_list_insert_1();
    test_list_insert_2();
    test_list_insert_3();
    test_list_insert_front_1();
    test_list_insert_front_2();
    test_list_reverse_1();
    test_list_reverse_2();
    test_list_copy_1();
    test_list_copy_2();
    test_list_from_args_1();
    return 0;
}
