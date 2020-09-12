#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../dlinked_list.h"


/* check appended integer node has the right value and correct prev pointer*/
void test_dlist_append_1() {
    DListNode *head = (DListNode *) malloc(sizeof(DListNode));
    int values[] = {1, 2};
    head->val = &values[0];
    head->prev = NULL;
    head->next = NULL;
    dlist_append(head, &values[1], INT);

    for (int i = 1; head != NULL; i++) {
        if (i == 2 && *(int *)head->prev->val != 1) {
            printf("test_dlist_append_1: FAILED\n");
            return;
        }
        if (i > 2 || *(int *)head->val != i) {
            printf("test_dlist_append_1: FAILED\n");
            return;
        }
        head = head->next;
    }
    printf("test_dlist_append_1: OK\n");
}


int main(int argc, char *argv[]) {
    test_dlist_append_1();
}
