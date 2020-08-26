#include <stdio.h>
#include <stdlib.h>
#include "../linked_list.h"


/* append float to list of length 1 */
void test_list_append_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    float values[] = {1, 2};
    head->val = &values[0];
    list_append(head, &values[1], sizeof(float));
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
            printf("test_list_append_1: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_append_1: PASS\n");
}


/* append int to list of length 1 */
void test_list_append_2() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    int values[2] = {1, 2};
    head->val = &values[0];
    list_append(head, &values[1], sizeof(int));
    for (int i = 1; head != NULL; i++) {
        if (i > 2 || *(int *)head->val != i) {
            printf("test_list_append_2: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_append_2: PASS\n");
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
    float values[] = {1.0, 2.0};
    head->val = &values[0];
    head->next = node1;
    node1->val = &values[1];
    ListNode *copy = list_copy(head);
    for (float i = 1.0; copy != NULL; i++) {
        if (i > 2.0 || *(float *)copy->val != i) {
            printf("test_list_copy_2: FAILED\n");
            return;
        }
        copy = copy->next;
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
    node1->val = &values[1];
    node2->val = &values[2];
    list_delete(head, 1);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
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
    float values[] = {0, 1, 2};
    head->val = &values[0];
    node1->val = &values[1];
    node2->val = &values[2];
    list_delete(head, 0);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
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
    float values[] = {1, 2, 3};
    head->val = &values[0];
    node1->val = &values[1];
    node2->val = &values[2];
    list_delete(head, 2);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 2.0 || *(float *)head->val != i) {
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
    float values[] = {1, 2, 3};
    head->val = &values[0];
    node1->val = &values[1];
    node2->val = &values[2];
    list_delete(head, 3);
    for (float i = 1.0; head != NULL; i++) {
        if (i > 3.0 || *(float *)head->val != i) {
            printf("test_list_delete_4: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_list_delete_4: PASS\n");
}


int main(int argc, char *argv[]) {
    test_list_append_1();
    test_list_append_2();
    test_list_copy_1();
    test_list_copy_2();
    test_list_delete_1();
    test_list_delete_2();
    test_list_delete_3();
    test_list_delete_4();
    return 0;
}
