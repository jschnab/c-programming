#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../dlinked_list.h"


static int n_fail = 0;


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
    printf("test_dlist_append_1: PASS\n");
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
    printf("test_dlist_append_2: PASS\n");
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
    printf("test_dlist_append_3: PASS\n");
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
    printf("test_dlist_append_4: PASS\n");
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
    printf("test_dlist_append_5: PASS\n");
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
    printf("test_dlist_append_6: PASS\n");
}


/* check list is correctly copied */
void test_dlist_copy_1() {
    DList *list = dlist_init();
    int values[] = {4, 5, 6};
    int i;
    for (i = 0; i < 3; i++)
        dlist_append(list, &values[i], INT);
    DList *copy = dlist_copy(list);

    if (copy->n != 3) {
        printf("test_dlist_copy_1: FAILED\n");
        n_fail++;
        return;
    }

    /* traverse list from head to tail */
    DListNode *current = copy->head;
    for (i = 0; current != NULL; i++) {
        if (
            *(int *)current->val != values[i] ||
            current->type != INT ||
            i > 2
        ) {
            printf("test_dlist_copy_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }

    /* traverse list from tail to head */
    current = copy->tail;
    for (i = 2; current != NULL; i--) {
        if (
            *(int *)current->val != values[i] ||
            current->type != INT ||
            i < 0
        ) {
            printf("test_dlist_copy_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_copy_1: PASS\n");
}


/* delete first node */
void test_dlist_delete_1() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7};
    int i;
    DListNode *current;
    for (i = 0; i < 3; i++)
        dlist_append(list, &values[i], INT);
    dlist_delete(list, 0);
    if (list->n != 2) {
        printf("test_dlist_delete_1: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = list->head;
    for (i = 1; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2 || current->type != INT) {
            printf("test_dlist_delete_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0 || current->type != INT) {
            printf("test_dlist_delete_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_delete_1: PASS\n");
}


/* delete middle node */
void test_dlist_delete_2() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7};
    int i;
    DListNode *current;
    dlist_append(list, &values[1], INT);
    dlist_append(list, &values[0], INT);
    dlist_append(list, &values[2], INT);
    dlist_delete(list, 1);
    if (list->n != 2) {
        printf("test_dlist_delete_2: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = list->head;
    for (i = 1; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2 || current->type != INT) {
            printf("test_dlist_delete_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0 || current->type != INT) {
            printf("test_dlist_delete_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_delete_2: PASS\n");
}


/* delete last node */
void test_dlist_delete_3() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7};
    int i;
    DListNode *current;
    for (i = 0; i < 3; i++)
        dlist_append(list, &values[i], INT);
    dlist_delete(list, 2);
    if (list->n != 2) {
        printf("test_dlist_delete_3: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 1 || current->type != INT) {
            printf("test_dlist_delete_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = list->tail;
    for (i = 1; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0 || current->type != INT) {
            printf("test_dlist_delete_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_delete_3: PASS\n");
}


/* delete first then last node */
void test_dlist_delete_4() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7, 8};
    int i;
    DListNode *current;
    for (i = 0; i < 4; i++)
        dlist_append(list, &values[i], INT);
    dlist_delete(list, 0);
    dlist_delete(list, 2);
    if (list->n != 2) {
        printf("test_dlist_delete_4: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = list->head;
    for (i = 1; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2 || current->type != INT) {
            printf("test_dlist_delete_4: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 1 || current->type != INT) {
            printf("test_dlist_delete_4: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_delete_4: PASS\n");
}


/* check string type is correctly returned */
void test_dlist_get_type_1() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (dlist_get_type(list, 0) != STRING) {
        printf("test_dlist_get_type_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_type_1: PASS\n");
}


/* check integer type is correctly returned */
void test_dlist_get_type_2() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (dlist_get_type(list, 1) != INT) {
        printf("test_dlist_get_type_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_type_2: PASS\n");
}


/* check float type is correctly returned */
void test_dlist_get_type_3() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (dlist_get_type(list, 2) != FLOAT) {
        printf("test_dlist_get_type_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_type_3: PASS\n");
}


/* check value of string is correctly returned */
void test_dlist_get_value_1() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (strcmp((char *)dlist_get_value(list, 0), s) != 0) {
        printf("test_dlist_get_value_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_value_1: PASS\n");
}


/* check value of integer is correctly returned */
void test_dlist_get_value_2() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (*(int *)dlist_get_value(list, 1) != i) {
        printf("test_dlist_get_value_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_value_2: PASS\n");
}


/* check value of float is correctly returned */
void test_dlist_get_value_3() {
    DList *list = dlist_init();
    char *s = "hello";
    int i = 5;
    float f = 3.14;
    dlist_append(list, s, STRING);
    dlist_append(list, &i, INT);
    dlist_append(list, &f, FLOAT);
    if (*(float *)dlist_get_value(list, 2) != f) {
        printf("test_dlist_get_value_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_get_value_3: PASS\n");
}


/* doubly-linked list is correcty initialized */
void test_dlist_init_1() {
    DList *list = dlist_init();
    if (list == NULL || list->head != NULL || list->tail != NULL || list->n != 0) {
        printf("test_dlist_init_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_init_1: PASS\n");
}


/* insert integer node in middle of linked list */
void test_dlist_insert_1() {
    DList *list = dlist_init();
    int values[] = {2, 3, 4};
    dlist_append(list, &values[0], INT);
    dlist_append(list, &values[2], INT);
    dlist_insert(&list, &values[1], INT, 1);

    /* check list length */
    if (list->n != 3) {
        printf("test_dlist_insert_1: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2) {
            printf("test_dlist_insert_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0) {
            printf("test_dlist_insert_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    
    printf("test_dlist_insert_1: PASS\n");
}


/* insert integer node at end of linked list */
void test_dlist_insert_2() {
    DList *list = dlist_init();
    int values[] = {2, 3, 4};
    dlist_append(list, &values[0], INT);
    dlist_append(list, &values[1], INT);
    dlist_insert(&list, &values[2], INT, 2);

    /* check list length */
    if (list->n != 3) {
        printf("test_dlist_insert_2: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2) {
            printf("test_dlist_insert_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0) {
            printf("test_dlist_insert_2: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    
    printf("test_dlist_insert_2: PASS\n");
}


/* insert integer node at beginning of linked list */
void test_dlist_insert_3() {
    DList *list = dlist_init();
    int values[] = {2, 3, 4};
    dlist_append(list, &values[1], INT);
    dlist_append(list, &values[2], INT);
    dlist_insert(&list, &values[0], INT, 0);

    /* check list length */
    if (list->n != 3) {
        printf("test_dlist_insert_3: FAILED\n");
        n_fail++;
        return;
    }

    int i;
    DListNode *current;
    /* traverse list from head to tail */
    current = list->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2) {
            printf("test_dlist_insert_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse list from tail to head */
    current = list->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0) {
            printf("test_dlist_insert_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    
    printf("test_dlist_insert_3: PASS\n");
}



/* get length of list */
void test_dlist_length_1() {
    DList *list = dlist_init();
    if (dlist_length(list) != 0) {
        printf("test_dlist_length_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_length_1: PASS\n");
}


/* print list of integers */
void test_dlist_print_1() {
    DList *list = dlist_init();
    int values[] = {2, 4, 6};
    for (int i = 0; i <= 2; i++)
        dlist_append(list, &values[i], INT);
    dlist_print(list);
}


/* print list of floats */
void test_dlist_print_2() {
    DList *list = dlist_init();
    float values[] = {3.14159, 6.28319, 12.56638};
    for (int i = 0; i <= 2; i++)
        dlist_append(list, &values[i], FLOAT);
    dlist_print(list);
}


/* print list of strings */
void test_dlist_print_3() {
    DList *list = dlist_init();
    char *values[] = {"brave", "new", "world"};
    for (int i = 0; i <= 2; i++)
        dlist_append(list, values[i], STRING);
    dlist_print(list);
}


int main(int argc, char *argv[]) {
    printf("Running tests on doubly-linked list functions...\n\n");
    test_dlist_append_1();
    test_dlist_append_2();
    test_dlist_append_3();
    test_dlist_append_4();
    test_dlist_append_5();
    test_dlist_append_6();
    test_dlist_copy_1();
    test_dlist_delete_1();
    test_dlist_delete_2();
    test_dlist_delete_3();
    test_dlist_delete_4();
    test_dlist_get_type_1();
    test_dlist_get_type_2();
    test_dlist_get_type_3();
    test_dlist_get_value_1();
    test_dlist_get_value_2();
    test_dlist_get_value_3();
    test_dlist_init_1();
    test_dlist_insert_1();
    test_dlist_insert_2();
    test_dlist_insert_3();
    test_dlist_length_1();
    test_dlist_print_1();
    test_dlist_print_2();
    test_dlist_print_3();
    printf("\nTests finished.\nNumber of failures: %d\n", n_fail);
}
