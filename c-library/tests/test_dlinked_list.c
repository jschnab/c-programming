#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../dlinked_list.h"


static int n_fail = 0;


/* doubly-linked list is correcty initialized */
void test_dlist_init_1() {
    DList *list = dlist_init();
    if (list == NULL || list->head != NULL || list->tail != NULL || list->n != 0) {
        printf("test_dlist_init_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_init_1: OK\n");
}


/* check integer node is correctly appended to empty list */
void test_dlist_append_1() {
    DList *list = dlist_init();
    int value = 3;
    dlist_append(list, &value, INT);
    if (list->n != 1 || *(int *)list->head->val != 3 || *(int *)list->tail->val != 3) {
        printf("test_dlist_append_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_append_1: OK\n");
}


/* check integer nodes correctly appended to list */
void test_dlist_append_2() {
    DList *list = dlist_init();
    int values[] = {4, 5, 6};
    dlist_append(list, &values[0], INT);
    dlist_append(list, &values[1], INT);
    dlist_append(list, &values[2], INT);
    if (list->n != 3) {
        printf("test_dlist_append_2: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2) {
            printf("test_dlist_append_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0) {
            printf("test_dlist_append_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_append_2: OK\n");
}


/* check float node is correctly appended to empty list */
void test_dlist_append_3() {
    DList *list = dlist_init();
    float value = 3.0;
    dlist_append(list, &value, FLOAT);
    if (list->n != 1 || *(float *)list->head->val != 3.0 || *(float *)list->tail->val != 3.0) {
        printf("test_dlist_append_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_append_3: OK\n");
}


/* check float nodes correctly appended to list */
void test_dlist_append_4() {
    DList *list = dlist_init();
    float values[] = {4.0, 5.0, 6.0};
    dlist_append(list, &values[0], FLOAT);
    dlist_append(list, &values[1], FLOAT);
    dlist_append(list, &values[2], FLOAT);
    if (list->n != 3) {
        printf("test_dlist_append_4: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(float *)current->val != values[i] || i > 2) {
            printf("test_dlist_append_4: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(float *)current->val != values[i] || i < 0) {
            printf("test_dlist_append_4: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_append_4: OK\n");
}


/* check string node is correctly appended to empty list */
void test_dlist_append_5() {
    DList *list = dlist_init();
    char *value = "hello";
    dlist_append(list, value, STRING);
    if (
        list->n != 1 ||
        strcmp((char *)list->head->val, value) != 0 ||
        strcmp((char *)list->tail->val, value) != 0
    ) {
        printf("test_dlist_append_5: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_append_5: OK\n");
}


/* check float nodes correctly appended to list */
void test_dlist_append_6() {
    DList *list = dlist_init();
    char *values[] = {"brave", "new", "world"};
    dlist_append(list, values[0], STRING);
    dlist_append(list, values[1], STRING);
    dlist_append(list, values[2], STRING);
    if (list->n != 3) {
        printf("test_dlist_append_6: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (strcmp((char *)current->val, values[i]) != 0 || i > 2) {
            printf("test_dlist_append_6: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (strcmp((char *)current->val, values[i]) != 0 || i < 0) {
            printf("test_dlist_append_6: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_append_6: OK\n");
}


int main(int argc, char *argv[]) {
    printf("Running tests on doubly-linked list functions...\n\n");
    test_dlist_init_1();
    test_dlist_append_1();
    test_dlist_append_2();
    test_dlist_append_3();
    test_dlist_append_4();
    test_dlist_append_5();
    test_dlist_append_6();

    printf("\nTests finished.\nNumber of failures: %d\n", n_fail);
}
