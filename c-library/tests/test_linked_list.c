#include <stdio.h>
#include <stdlib.h>
#include "../linked_list.h"


/* append float to list of length 1 */
void test_list_append_1() {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    float values[2] = {1, 2};
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


int main(int argc, char *argv[]) {
    test_list_append_1();
    return 0;
}
