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


/* check two empty lists are considered equal */
void test_dlist_equal_1() {
    DList *a = dlist_init();
    DList *b = dlist_init();
    if (dlist_equal(a, b) != 1) {
        printf("test_dlist_equal_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_equal_1: PASS\n");
}


/* check lists of integers are considered equal */
void test_dlist_equal_2() {
    DList *a = dlist_init();
    DList *b = dlist_init();
    int values[] = {5, 6, 7};
    for (int i = 0; i < 3; i++) {
        dlist_append(a, &values[i], INT);
        dlist_append(b, &values[i], INT);
    }
    if (dlist_equal(a, b) != 1) {
        printf("test_dlist_equal_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_equal_2: PASS\n");
}


/* check lists of floats are considered equal */
void test_dlist_equal_3() {
    DList *a = dlist_init();
    DList *b = dlist_init();
    float values[] = {5.0, 6.0, 7.0};
    for (int i = 0; i < 3; i++) {
        dlist_append(a, &values[i], FLOAT);
        dlist_append(b, &values[i], FLOAT);
    }
    if (dlist_equal(a, b) != 1) {
        printf("test_dlist_equal_3: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_equal_3: PASS\n");
}


/* check lists of strings are considered equal */
void test_dlist_equal_4() {
    DList *a = dlist_init();
    DList *b = dlist_init();
    char *values[] = {"brave", "new", "world"};
    for (int i = 0; i < 3; i++) {
        dlist_append(a, &values[i], STRING);
        dlist_append(b, &values[i], STRING);
    }
    if (dlist_equal(a, b) != 1) {
        printf("test_dlist_equal_4: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_equal_4: PASS\n");
}


/* check lists of integers with same values but different lengths
 * are considered unequal */
void test_dlist_equal_5() {
    DList *a = dlist_init();
    DList *b = dlist_init();
    int values[] = {5, 6, 7};
    dlist_append(a, &values[0], INT);
    dlist_append(a, &values[1], INT);
    dlist_append(b, &values[0], INT);
    dlist_append(b, &values[1], INT);
    dlist_append(b, &values[2], INT);
    if (dlist_equal(a, b) != 0) {
        printf("test_dlist_equal_5: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_equal_5: PASS\n");
}


/* convert integer array to list */
void test_dlist_from_array_1() {
    int array[] = {3, 4, 5, 6};
    DList *list = dlist_from_array(array, INT, 4);
    DListNode *head = list->head;
    DListNode *tail = list->tail;
    if (list->n != 4 || head == NULL || tail == NULL) {
        printf("test_dlist_from_array_1: FAILED\n");
        n_fail++;
        return;
    }
    for (int i = 0; head != NULL; i++) {
        if (*(int *)head->val != array[i] || head->type != INT || i > 3) {
            printf("test_dlist_from_array_1: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    for (int i = 3; tail != NULL; i--) {
        if (*(int *)tail->val != array[i] || tail->type != INT || i < 0) {
            printf("test_dlist_from_array_1: FAILED\n");
            n_fail++;
            return;
        }
        tail = tail->prev;
    }
    printf("test_dlist_from_array_1: PASS\n");
}


/* convert float array to list */
void test_dlist_from_array_2() {
    float array[] = {9.0, 8.0, 7.0, 6.0};
    DList *list = dlist_from_array(array, FLOAT, 4);
    DListNode *head = list->head;
    DListNode *tail = list->tail;
    if (list->n != 4 || head == NULL || tail == NULL) {
        printf("test_dlist_from_array_2: FAILED\n");
        n_fail++;
        return;
    }
    for (int i = 0; head != NULL; i++) {
        if (*(float *)head->val != array[i] || head->type != FLOAT || i > 3) {
            printf("test_dlist_from_array_2: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    for (int i = 3; tail != NULL; i--) {
        if (*(float *)tail->val != array[i] || tail->type != FLOAT || i < 0) {
            printf("test_dlist_from_array_2: FAILED\n");
            n_fail++;
            return;
        }
        tail = tail->prev;
    }
    printf("test_dlist_from_array_2: PASS\n");
}


/* convert string array to list */
void test_dlist_from_array_3() {
    char *array[] = {"hello", "brave", "new", "world"};
    DList *list = dlist_from_array(array, STRING, 4);
    DListNode *head = list->head;
    DListNode *tail = list->tail;
    if (list->n != 4 || head == NULL || tail == NULL) {
        printf("test_dlist_from_array_3: FAILED\n");
        n_fail++;
        return;
    }
    for (int i = 0; head != NULL; i++) {
        if (strcmp((char *)head->val, array[i]) != 0 || head->type != STRING || i > 3) {
            printf("test_dlist_from_array_3: FAILED\n");
            n_fail++;
            return;
        }
        head = head->next;
    }
    for (int i = 3; tail != NULL; i--) {
        if (strcmp((char *)tail->val, array[i]) != 0 || tail->type != STRING || i < 0) {
            printf("test_dlist_from_array_3: FAILED\n");
            n_fail++;
            return;
        }
        tail = tail->prev;
    }
    printf("test_dlist_from_array_3: PASS\n");
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


/* slice list of integers on both ends*/
void test_dlist_slice_1() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7, 8};
    int i;
    DListNode *current;
    for (i = 0; i < 4; i++)
        dlist_append(list, &values[i], INT);
    DList *sliced = dlist_slice(list, 1, 3);
    if (sliced->n != 2) {
        printf("test_dlist_slice_1: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = sliced->head;
    for (i = 1; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 2 || current->type != INT) {
            printf("test_dlist_slice_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = sliced->tail;
    for (i = 2; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 1 || current->type != INT) {
            printf("test_dlist_slice_1: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_slice_1: PASS\n");
}


/* slice list of integers into empty list*/
void test_dlist_slice_2() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7, 8};
    for (int i = 0; i < 4; i++)
        dlist_append(list, &values[i], INT);
    DList *sliced = dlist_slice(list, 1, 1);
    if (sliced->n != 0 || sliced->head != NULL || sliced->tail != NULL) {
        printf("test_dlist_slice_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_dlist_slice_2: PASS\n");
}


/* slice list of integers into the same list*/
void test_dlist_slice_3() {
    DList *list = dlist_init();
    int values[] = {5, 6, 7, 8};
    int i;
    DListNode *current;
    for (i = 0; i < 4; i++)
        dlist_append(list, &values[i], INT);
    DList *sliced = dlist_slice(list, 0, 4);
    if (sliced->n != 4) {
        printf("test_dlist_slice_3: FAILED\n");
        n_fail++;
        return;
    }
    /* traverse from head to tail */
    current = sliced->head;
    for (i = 0; current != NULL; i++) {
        if (*(int *)current->val != values[i] || i > 3 || current->type != INT) {
            printf("test_dlist_slice_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->next;
    }
    /* traverse from tail to head */
    current = sliced->tail;
    for (i = 3; current != NULL; i--) {
        if (*(int *)current->val != values[i] || i < 0 || current->type != INT) {
            printf("test_dlist_slice_3: FAILED\n");
            n_fail++;
            return;
        }
        current = current->prev;
    }
    printf("test_dlist_slice_3: PASS\n");
}


/* convert list into array of integers */
void test_dlist_to_array_1() {
    DList *list = dlist_init();
    int values[] = {3, 4, 5};
    int i;
    for (i = 0; i < 3; i++)
        dlist_append(list, &values[i], INT);
    int result[3];
    dlist_to_array(list, result, INT);
    for (i = 0; i < 3; i++)
        if (result[i] != values[i]) {
            printf("test_dlist_to_array_1: FAILED\n");
            n_fail++;
            return;
        }
    printf("test_dlist_to_array_1: PASS\n");
}


/* convert list into array of integers */
void test_dlist_to_array_2() {
    DList *list = dlist_init();
    float values[] = {3.0, 4.0, 5.0};
    int i;
    for (i = 0; i < 3; i++)
        dlist_append(list, &values[i], FLOAT);
    int result[3];
    dlist_to_array(list, result, FLOAT);
    for (i = 0; i < 3; i++)
        if (result[i] != values[i]) {
            printf("test_dlist_to_array_2: FAILED\n");
            n_fail++;
            return;
        }
    printf("test_dlist_to_array_2: PASS\n");
}


/* convert list containing 3 string nodes to array */
void test_dlist_to_strarray_1() {
    DList *list = dlist_init();
    char *values[] = {"brave", "new", "world"};
    int i;
    for (i = 0; i < 3; i++)
        dlist_append(list, values[i], STRING);
    char *array[3];
    dlist_to_strarray(list, array);
    for (i = 0; i < 3; i++) {
        if (strcmp(array[i], values[i]) != 0) {
            printf("test_dlist_to_strarray_1: FAILED\n");
            n_fail++;
            return;
        }
    }
    printf("test_dlist_to_array_1: PASS\n");
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
    test_dlist_equal_1();
    test_dlist_equal_2();
    test_dlist_equal_3();
    test_dlist_equal_4();
    test_dlist_equal_5();
    test_dlist_from_array_1();
    test_dlist_from_array_2();
    test_dlist_from_array_3();
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
    test_dlist_slice_1();
    test_dlist_slice_2();
    test_dlist_slice_3();
    test_dlist_to_array_1();
    test_dlist_to_array_2();
    test_dlist_to_strarray_1();
    test_dlist_print_1();
    test_dlist_print_2();
    test_dlist_print_3();
    printf("\nTests finished.\nNumber of failures: %d\n", n_fail);
}
