#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_types.h"
#include "../dynamic_array.h"

static int n_fail = 0;


/* append integers to array */
void test_darray_append_1() {
    int values[] = {4, 5, 6};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    for (i = 0; i < 3; i++) {
        if (((int *)array->items)[i] != values[i]) {
            n_fail++;
            printf("test_darray_append_1: FAILED\n");
            return;
        }
    }
    if (array->count != 3) {
        n_fail++;
        printf("test_darray_append_1: FAILED\n");
        return;
    }
    printf("test_darray_append_1: PASS\n");
}


/* append floats to array */
void test_darray_append_2() {
    float values[] = {2.0, 3.0, 4.0};
    DArray *array = darray_init(FLOAT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    for (i = 0; i < 3; i++) {
        if (((float *)array->items)[i] != values[i]) {
            n_fail++;
            printf("test_darray_append_2: FAILED\n");
            return;
        }
    }
    if (array->count != 3) {
        if (((float *)array->items)[i] != values[i]) {
            n_fail++;
            printf("test_darray_append_2: FAILED\n");
            return;
        }
    }
    printf("test_darray_append_2: PASS\n");
}


/* append strings to array */
void test_darray_append_3() {
    char *values[] = {"brave", "new", "world"};
    DArray *array = darray_init(STRING);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, values[i]);
    }
    for (i = 0; i < 3; i++) {
        if (strcmp(((char **)array->items)[i], values[i]) != 0) {
            n_fail++;
            printf("test_darray_append_3: FAILED\n");
            return;
        }
    }
    if (array->count != 3) {
        n_fail++;
        printf("test_darray_append_3: FAILED\n");
        return;
    }
    printf("test_darray_append_3: PASS\n");
}


/* compare two integer items where A > B */
void test_darray_compare_items_1() {
    int values[] = {3, 4, 4};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    if (darray_compare_items(array, 1, 0) != 1) {
        n_fail++;
        printf("test_darray_compare_items_1: FAILED\n");
        return;
    }
    printf("test_darray_compare_items_1: PASS\n");
}


/* compare two integer items where A < B */
void test_darray_compare_items_2() {
    int values[] = {3, 4, 4};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    if (darray_compare_items(array, 0, 1) != -1) {
        n_fail++;
        printf("test_darray_compare_items_2: FAILED\n");
        return;
    }
    printf("test_darray_compare_items_2: PASS\n");
}


/* compare two integer items where A = B */
void test_darray_compare_items_3() {
    int values[] = {3, 4, 4};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    if (darray_compare_items(array, 1, 1) != 0) {
        n_fail++;
        printf("test_darray_compare_items_3: FAILED\n");
        return;
    }
    printf("test_darray_compare_items_3: PASS\n");
}


/* initialize an integer array with wrapper function */
void test_darray_init_1() {
    DArray *array = darray_init(INT);
    if (
        array->type != INT ||
        /* may have to update if base size changes in dynamic_array.c */
        array->size != 30 ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_1: FAILED\n");
        return;
    }
    printf("test_darray_init_1: PASS\n");
}


/* initialize a float array with wrapper function */
void test_darray_init_2() {
    DArray *array = darray_init(FLOAT);
    if (
        array->type != FLOAT ||
        /* may have to update if base size changes in dynamic_array.c */
        array->size != 30 ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_2: FAILED\n");
        return;
    }
    printf("test_darray_init_2: PASS\n");
}


/* initialize a string array with wrapper function */
void test_darray_init_3() {
    DArray *array = darray_init(STRING);
    if (
        array->type != STRING ||
        array->size != 30 ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_3: FAILD\n");
        return;
    }
    printf("test_darray_init_3: PASS\n");
}


/* initialize an integer array and specify array size */
void test_darray_init_sized_1() {
    char type = INT;
    int size = 10;
    DArray *array = darray_init_sized(type, size);
    if (
        array->type != type ||
        array->size != size ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_sized_1: FAILED\n");
        return;
    }
    printf("test_darray_init_sized_1: PASS\n");
}


/* initialize a float array and specify array size */
void test_darray_init_sized_2() {
    char type = FLOAT;
    int size = 10;
    DArray *array = darray_init_sized(type, size);
    if (
        array->type != type ||
        array->size != size ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_sized_2: FAILED\n");
        return;
    }
    printf("test_darray_init_sized_2: PASS\n");
}


/* initialize a string array and specify array size */
void test_darray_init_sized_3() {
    char type = STRING;
    int size = 10;
    DArray *array = darray_init_sized(type, size);
    if (
        array->type != type ||
        array->size != size ||
        array->count != 0
    ) {
        n_fail++;
        printf("test_darray_init_sized_3: FAILED\n");
        return;
    }
    printf("test_darray_init_sized_3: PASS\n");
}


/* pop item from integer array */
void test_darray_pop_1() {
    int values[] = {4, 5, 6};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    void *pop = darray_pop(array);
    for (i = 0; i < 2; i++) {
        if (((int *)array->items)[i] != values[i]) {
            n_fail++;
            printf("test_darray_pop_1: FAILED\n");
            return;
        }
    }
    if (array->count != 2 || *(int *)pop != values[2]) {
        n_fail++;
        printf("test_darray_pop_1: FAILED\n");
        return;
    }
    printf("test_darray_pop_1: PASS\n");
}


/* pop item from float array */
void test_darray_pop_2() {
    float values[] = {2.0, 3.0, 4.0};
    DArray *array = darray_init(FLOAT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    float pop = *(float *)darray_pop(array);
    for (i = 0; i < 2; i++) {
        if (((float *)array->items)[i] != values[i]) {
            n_fail++;
            printf("test_darray_pop_2: FAILED\n");
            return;
        }
    }
    if (array->count != 2 || pop != values[2]) {
        n_fail++;
        printf("test_darray_pop_2: FAILED\n");
        return;
    }
    printf("test_darray_pop_2: PASS\n");
}


/* pop item from string array */
void test_darray_pop_3() {
    char *values[] = {"brave", "new", "world"};
    DArray *array = darray_init(STRING);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, values[i]);
    }
    char *pop = (char *)darray_pop(array);
    for (i = 0; i < 2; i++) {
        if (strcmp(((char **)array->items)[i], values[i]) != 0) {
            n_fail++;
            printf("test_darray_pop_3: FAILED\n");
            return;
        }
    }
    if (array->count != 2 || strcmp(pop, values[2]) != 0) {
        n_fail++;
        printf("test_darray_pop_3: FAILED\n");
        return;
    }
    printf("test_darray_pop_3: PASS\n");
}


/* sort odd number of integers with quicksort */
void test_darray_quicksort_1() {
    int values[] = {12, 9, 7, 12, 10, 14};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 6; i++) {
        darray_append(array, &values[i]);
    }
    darray_quicksort(array, 0, array->count-1);
    for (i = 1; i < 6; i++) {
        if (((int *)array->items)[i-1] > ((int *)array->items)[i]) {
            n_fail++;
            printf("test_darray_quicksort_1: FAILED\n");
            return;
        }
    }
    printf("test_darray_quicksort_1: PASS\n");
}


/* sort even number of integers with quicksort */
void test_darray_quicksort_2() {
    int values[] = {99, 5, -1, 0};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 4; i++) {
        darray_append(array, &values[i]);
    }
    darray_quicksort(array, 0, array->count-1);
    for (i = 1; i < 4; i++) {
        if (((int *)array->items)[i-1] > ((int *)array->items)[i]) {
            n_fail++;
            printf("test_darray_quicksort_2: FAILED\n");
            return;
        }
    }
    printf("test_darray_quicksort_2: PASS\n");
}


/* swap integer items */
void test_darray_swap_items_1() {
    int values[] = {4, 5, 6};
    DArray *array = darray_init(INT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    darray_swap_items(array, 0, 2);
    if (
        ((int *)array->items)[0] != 6 ||
        ((int *)array->items)[1] != 5 ||
        ((int *)array->items)[2] != 4
    ) {
        n_fail++;
        printf("test_darray_swap_items_1: FAILED\n");
        return;
    }
    printf("test_darray_swap_items_1: PASS\n");
}


/* swap float items */
void test_darray_swap_items_2() {
    float values[] = {2.0, 3.0, 4.0};
    DArray *array = darray_init(FLOAT);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, &values[i]);
    }
    darray_swap_items(array, 0, 2);
    if (
        ((float *)array->items)[0] != 4.0 ||
        ((float *)array->items)[1] != 3.0 ||
        ((float *)array->items)[2] != 2.0
    ) {
        n_fail++;
        printf("test_darray_swap_items_2: FAILED\n");
        return;
    }
    printf("test_darray_swap_items_2: PASS\n");
}


/* swap string items */
void test_darray_swap_items_3() {
    char *values[] = {"brave", "new", "world"};
    DArray *array = darray_init(STRING);
    int i;
    for (i = 0; i < 3; i++) {
        darray_append(array, values[i]);
    }
    darray_swap_items(array, 0, 2);
    if (
        strcmp(((char **)array->items)[0], values[2]) != 0 ||
        strcmp(((char **)array->items)[1], values[1]) != 0 ||
        strcmp(((char **)array->items)[2], values[0]) != 0
    ) {
        n_fail++;
        printf("test_darray_swap_items_3: FAILED\n");
        return;
    }
    printf("test_darray_swap_items_3: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running tests for dynamic array...\n\n");
    test_darray_append_1();
    test_darray_append_2();
    test_darray_append_3();
    test_darray_compare_items_1();
    test_darray_compare_items_2();
    test_darray_compare_items_3();
    test_darray_init_1();
    test_darray_init_2();
    test_darray_init_3();
    test_darray_init_sized_1();
    test_darray_init_sized_2();
    test_darray_init_sized_3();
    test_darray_pop_1();
    test_darray_pop_2();
    test_darray_pop_3();
    test_darray_quicksort_1();
    test_darray_quicksort_2();
    test_darray_swap_items_1();
    test_darray_swap_items_2();
    test_darray_swap_items_3();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
