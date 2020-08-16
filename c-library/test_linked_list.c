#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void test_list_to_array_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    int array[1] = {0};
    list_to_array(head, array);
    if (array[0] != 0) {
        printf("test_list_to_array_1: FAILED\n");
        return;
    }
    printf("test_list_to_array_1: PASS\n");
}


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


int main(int argc, char *argv[]) {
    test_list_to_array_1();
    test_list_to_array_2();
    return 0;
}
