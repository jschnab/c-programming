#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_types.h"
#include "../heap.h"


static int n_fail = 0;


/* add integer items to linked list */
void test_heap_add_1() {
    Heap *heap = heap_init(INT);
    int values[] = {71, 15, 36, 57, 101};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, &values[i]);
    if (
        ((int *)heap->items)[0] != values[4] ||
        ((int *)heap->items)[1] != values[0] ||
        ((int *)heap->items)[2] != values[2] ||
        ((int *)heap->items)[3] != values[1] ||
        ((int *)heap->items)[4] != values[3] ||
        heap->count != 5
    ) {
        n_fail++;
        printf("test_heap_add_1: FAILED\n");
        return;
    }
    printf("test_heap_add_1: PASS\n");
}


/* add float item to linked list */
void test_heap_add_2() {
    Heap *heap = heap_init(FLOAT);
    float values[] = {71.0, 15.0, 36.0, 57.0, 101.0};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, &values[i]);
    if (
        ((float *)heap->items)[0] != values[4] ||
        ((float *)heap->items)[1] != values[0] ||
        ((float *)heap->items)[2] != values[2] ||
        ((float *)heap->items)[3] != values[1] ||
        ((float *)heap->items)[4] != values[3] ||
        heap->count != 5
    ) {
        n_fail++;
        printf("test_heap_add_2: FAILED\n");
        return;
    }
    printf("test_heap_add_2: PASS\n");
}


/* add string item to linked list */
void test_heap_add_3() {
    Heap *heap = heap_init(STRING);
    char *values[] = {"oh", "brave", "hello", "new", "world"};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, values[i]);
    if (
        strcmp(((char **)heap->items)[0], values[4]) != 0 ||
        strcmp(((char **)heap->items)[1], values[0]) != 0 ||
        strcmp(((char **)heap->items)[2], values[2]) != 0 ||
        strcmp(((char **)heap->items)[3], values[1]) != 0 ||
        strcmp(((char **)heap->items)[4], values[3]) != 0 ||
        heap->count != 5
    ) {
        n_fail++;
        printf("test_heap_add_3: FAILED\n");
        return;
    }
    printf("test_heap_add_3: PASS\n");
}


/* compare integers heap items a and b with a > b */
void test_heap_compare_items_1() {
    char type = INT;
    Heap *heap = heap_init(type);
    int values[] = {5, 2};
    ((int *)heap->items)[0] = values[0];
    ((int *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 1) {
        n_fail++;
        printf("test_heap_compare_items_1: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_1: PASS\n");
}


/* compare integers heap items a and b with a < b */
void test_heap_compare_items_2() {
    char type = INT;
    Heap *heap = heap_init(type);
    int values[] = {99, 100};
    ((int *)heap->items)[0] = values[0];
    ((int *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != -1) {
        n_fail++;
        printf("test_heap_compare_items_2: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_2: PASS\n");
}


/* compare integers heap items a and b with a = b */
void test_heap_compare_items_3() {
    char type = INT;
    Heap *heap = heap_init(type);
    int values[] = {3, 3};
    ((int *)heap->items)[0] = values[0];
    ((int *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 0) {
        n_fail++;
        printf("test_heap_compare_items_3: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_3: PASS\n");
}


/* compare float heap items a and b with a > b */
void test_heap_compare_items_4() {
    char type = FLOAT;
    Heap *heap = heap_init(type);
    float values[] = {50.0, 20.0};
    ((float *)heap->items)[0] = values[0];
    ((float *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 1) {
        n_fail++;
        printf("test_heap_compare_items_4: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_4: PASS\n");
}


/* compare float heap items a and b with a < b */
void test_heap_compare_items_5() {
    char type = FLOAT;
    Heap *heap = heap_init(type);
    float values[] = {10.0, 20.0};
    ((float *)heap->items)[0] = values[0];
    ((float *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != -1) {
        n_fail++;
        printf("test_heap_compare_items_5: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_5: PASS\n");
}


/* compare float heap items a and b with a = b */
void test_heap_compare_items_6() {
    char type = FLOAT;
    Heap *heap = heap_init(type);
    float values[] = {30.0, 30.0};
    ((float *)heap->items)[0] = values[0];
    ((float *)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 0) {
        n_fail++;
        printf("test_heap_compare_items_6: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_6: PASS\n");
}


/* compare string heap items a and b with a > b */
void test_heap_compare_items_7() {
    char type = STRING;
    Heap *heap = heap_init(type);
    char *values[] = {"world", "hello"};
    ((char **)heap->items)[0] = values[0];
    ((char **)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 1) {
        n_fail++;
        printf("test_heap_compare_items_7: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_7: PASS\n");
}


/* compare string heap items a and b with a < b */
void test_heap_compare_items_8() {
    char type = STRING;
    Heap *heap = heap_init(type);
    char *values[] = {"hello", "world"};
    ((char **)heap->items)[0] = values[0];
    ((char **)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != -1) {
        n_fail++;
        printf("test_heap_compare_items_8: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_8: PASS\n");
}


/* compare string heap items a and b with a = b */
void test_heap_compare_items_9() {
    char type = STRING;
    Heap *heap = heap_init(type);
    char *values[] = {"hello", "hello"};
    ((char **)heap->items)[0] = values[0];
    ((char **)heap->items)[1] = values[1];
    if (heap_compare_items(heap, 0, 1) != 0) {
        n_fail++;
        printf("test_heap_compare_items_9: FAILED\n");
        return;
    }
    printf("test_heap_compare_items_9: PASS\n");
}


/* delete heap with integer items*/
void test_heap_delete_1() {
    Heap *heap = heap_init(INT);
    int values[] = {1, 2};
    heap_add(heap, &values[0]);
    heap_add(heap, &values[1]);
    heap_delete(heap);
    printf("test_heap_delete_1: PASS\n");
}


/* delete heap with string items*/
void test_heap_delete_2() {
    Heap *heap = heap_init(INT);
    char *values[] = {"oh", "brave"};
    heap_add(heap, values[0]);
    heap_add(heap, values[1]);
    heap_delete(heap);
    printf("test_heap_delete_2: PASS\n");
}


/* delete integer item */
void test_heap_delete_item_1() {
    Heap *heap = heap_init(INT);
    int values[] = {71, 15, 36};
    int i;
    for (i = 0; i < 3; i++)
        heap_add(heap, &values[i]);
    heap_delete_item(heap, 2);
    if (
        ((int *)heap->items)[0] != values[0] ||
        ((int *)heap->items)[1] != values[1] ||
        ((int *)heap->items)[2] != 0 ||
        heap->count != 2
    ) {
        n_fail++;
        printf("test_heap_delete_item_1: FAILED\n");
        return;
    }
    printf("test_heap_delete_item_1: PASS\n");
}


/* delete float item */
void test_heap_delete_item_2() {
    Heap *heap = heap_init(FLOAT);
    float values[] = {71.0, 15.0, 36.0};
    int i;
    for (i = 0; i < 3; i++)
        heap_add(heap, &values[i]);
    heap_delete_item(heap, 2);
    if (
        ((float *)heap->items)[0] != values[0] ||
        ((float *)heap->items)[1] != values[1] ||
        ((float *)heap->items)[2] != 0 ||
        heap->count != 2
    ) {
        n_fail++;
        printf("test_heap_delete_item_2: FAILED\n");
        return;
    }
    printf("test_heap_delete_item_2: PASS\n");
}


/* delete string item */
void test_heap_delete_item_3() {
    Heap *heap = heap_init(STRING);
    char *values[] = {"oh", "brave", "hello"};
    int i;
    for (i = 0; i < 3; i++)
        heap_add(heap, values[i]);
    heap_delete_item(heap, 2);
    if (
        strcmp(((char **)heap->items)[0], values[0]) != 0 ||
        strcmp(((char **)heap->items)[1], values[1]) != 0 ||
        heap->count != 2
    ) {
        n_fail++;
        printf("test_heap_delete_item_3: FAILED\n");
        return;
    }
    printf("test_heap_delete_item_3: PASS\n");
}


/* initialization of heap of integers */
void test_heap_init_sized_1() {
    int base_size = 30;
    char type = INT;
    Heap *heap = heap_init_sized(base_size, type);
    if (
        heap->type != type ||
        heap->size != base_size ||
        heap->count != 0
    ) {
        n_fail++;
        printf("test_heap_init_sized_1: FAILED\n");
        return;
    }
    printf("test_heap_init_sized_1: PASS\n");
}


/* initialization of heap of floats */
void test_heap_init_sized_2() {
    int base_size = 30;
    char type = FLOAT;
    Heap *heap = heap_init_sized(base_size, type);
    if (
        heap->type != type ||
        heap->size != base_size ||
        heap->count != 0
    ) {
        n_fail++;
        printf("test_heap_init_sized_2: FAILED\n");
        return;
    }
    printf("test_heap_init_sized_2: PASS\n");
}


/* initialization of heap of strings */
void test_heap_init_sized_3() {
    int base_size = 30;
    char type = STRING;
    Heap *heap = heap_init_sized(base_size, type);
    if (
        heap->type != type ||
        heap->size != base_size ||
        heap->count != 0
    ) {
        n_fail++;
        printf("test_heap_init_sized_3: FAILED\n");
        return;
    }
    printf("test_heap_init_sized_3: PASS\n");
}


/* get index of parent from odd child index */
void test_heap_parent_index_1() {
    if (heap_parent_index(1) != 0) {
        n_fail++;
        printf("test_heap_parent_index_1: FAILED\n");
        return;
    }
    printf("test_heap_parent_index_1: PASS\n");
}


/* get index of parent from even child index */
void test_heap_parent_index_2() {
    if (heap_parent_index(4) != 1) {
        n_fail++;
        printf("test_heap_parent_index_2: FAILED\n");
        return;
    }
    printf("test_heap_parent_index_2: PASS\n");
}


/* pop integer item */
void test_heap_pop_1() {
    Heap *heap = heap_init(INT);
    int values[] = {71, 15, 36, 57, 101};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, &values[i]);
    int *result = heap_pop(heap);
    if (
        *result != 101 ||
        heap->count != 4
    ) {
        n_fail++;
        printf("test_heap_pop_1: FAILED\n");
        return;
    }
    printf("test_heap_pop_1: PASS\n");
}


/* pop float item */
void test_heap_pop_2() {
    Heap *heap = heap_init(FLOAT);
    float values[] = {71.0, 15.0, 36.0, 57.0, 101.0};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, &values[i]);
    float *result = heap_pop(heap);
    if (
        *result != values[4] ||
        heap->count != 4
    ) {
        n_fail++;
        printf("test_heap_pop_2: FAILED\n");
        return;
    }
    printf("test_heap_pop_2: PASS\n");
}


/* pop string item */
void test_heap_pop_3() {
    Heap *heap = heap_init(STRING);
    char *values[] = {"oh", "brave", "hello", "new", "world"};
    int i;
    for (i = 0; i < 5; i++)
        heap_add(heap, values[i]);
    char *result = heap_pop(heap);
    if (
        strcmp(result, values[4]) != 0 ||
        heap->count != 4
    ) {
        n_fail++;
        printf("test_heap_pop_3: FAILED\n");
        return;
    }
    printf("test_heap_pop_3: PASS\n");
}


/* get index of left child */
void test_heap_left_child_index_1() {
    if (heap_left_child_index(0) != 1) {
        n_fail++;
        printf("test_heap_left_child_index_1: FAILED\n");
        return;
    }
    printf("test_heap_left_child_index_1: PASS\n");
}

/* get index of right child */
void test_heap_right_child_index_1() {
    if (heap_right_child_index(0) != 2) {
        n_fail++;
        printf("test_heap_right_child_index_1: FAILED\n");
        return;
    }
    printf("test_heap_right_child_index_1: PASS\n");
}


/* swapping items */
void test_swapping_items_1() {
    Heap *heap = heap_init(INT);
    int values[] = {13, 27, 1};
    int i;
    for (i = 0; i < 3; i++) {
        /* show address via array subscripting or pointer arithmetic */
        printf("addr of items[%d]: %p\n", i, &((int *)heap->items)[i]);
        printf("addr of items[%d]: %p\n", i, (int *)heap->items+i);

        /* assign value via array subscripting or pointer arithmetic */
        ((int *)heap->items)[i] = ((int *)values)[i];
        *((int *)heap->items+i) = *((int *)values+i);

        /* print value via subscripting or pointer arithmetic */
        printf("heap->items[%d] = %d\n", i, *((int *)heap->items+i));
        printf("heap->items[%d] = %d\n", i, ((int *)heap->items)[i]);
    }
}


/* sift integer item down from first position in array */
void test_heap_sift_down_1() {
    Heap *heap = heap_init(INT);
    int values[] = {57, 71, 36, 15, 101};
    for (int i = 0; i < 5; i++) {
        ((int *)heap->items)[i] = values[i];
        heap->count++;
    }
    heap_sift_down(heap, 0, heap->count-1);
    if (
        ((int *)heap->items)[0] != 71 ||
        ((int *)heap->items)[1] != 57 ||
        ((int *)heap->items)[2] != 36 ||
        ((int *)heap->items)[3] != 15 ||
        ((int *)heap->items)[4] != 101 ||
        heap->count != 5
    ) {
        n_fail++;
        printf("test_heap_sift_down_1: FAILED\n");
        return;
    }
    printf("test_heap_sift_down_1: PASS\n");
}


/* sift item from last position in array */
void test_heap_sift_up_1() {
    Heap *heap = heap_init(INT);
    int values[] = {71, 57, 36, 15, 101};
    for (int i = 0; i < 5; i++) {
        ((int *)heap->items)[i] = values[i];
    }
    heap_sift_up(heap, 4);
    if (
        ((int *)heap->items)[0] != 101 ||
        ((int *)heap->items)[1] != 71 ||
        ((int *)heap->items)[2] != 36 ||
        ((int *)heap->items)[3] != 15 ||
        ((int *)heap->items)[4] != 57
    ) {
        n_fail++;
        printf("test_sift_up_1: FAILED\n");
        return;
    }
    printf("test_sift_up_1: PASS\n");
}


/* swap two integer heap items */
void test_heap_swap_items_1() {
    Heap *heap = heap_init(INT);
    ((int *)heap->items)[0] = 91;
    ((int *)heap->items)[1] = 78;
    heap_swap_items(heap, 0, 1);
    if (((int *)heap->items)[0] != 78 || ((int *)heap->items)[1] != 91) {
        n_fail++;
        printf("test_heap_swap_items_1: FAILED\n");
        return;
    }
    printf("test_heap_swap_items_1: PASS\n");
}


/* swap two float heap items */
void test_heap_swap_items_2() {
    Heap *heap = heap_init(FLOAT);
    float values[] = {3.14, 2.72};
    ((float *)heap->items)[0] = values[0];
    ((float *)heap->items)[1] = values[1];
    heap_swap_items(heap, 0, 1);
    /* remember floats do not have an exact representation */
    if (((float *)heap->items)[0] != values[1] || ((float *)heap->items)[1] != values[0]) {
        n_fail++;
        printf("test_heap_swap_items_2: FAILED\n");
        return;
    }
    printf("test_heap_swap_items_2: PASS\n");
}


/* swap two string heap items */
void test_heap_swap_items_3() {
    Heap *heap = heap_init(STRING);
    char *values[] = {"hello", "world"};
    ((char **)heap->items)[0] = values[0];
    ((char **)heap->items)[1] = values[1];
    heap_swap_items(heap, 0, 1);
    if (
        strcmp(((char **)heap->items)[0], values[1]) != 0 || 
        strcmp(((char **)heap->items)[1], values[0]) != 0
    ) {
        n_fail++;
        printf("test_heap_swap_items_3: FAILED\n");
        return;
    }
    printf("test_heap_swap_items_3: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for heap...\n\n");
    test_heap_add_1();
    test_heap_add_2();
    test_heap_add_3();
    test_heap_compare_items_1();
    test_heap_compare_items_2();
    test_heap_compare_items_3();
    test_heap_compare_items_4();
    test_heap_compare_items_5();
    test_heap_compare_items_6();
    test_heap_compare_items_7();
    test_heap_compare_items_8();
    test_heap_compare_items_9();
    test_heap_delete_1();
    test_heap_delete_2();
    test_heap_delete_item_1();
    test_heap_delete_item_2();
    test_heap_delete_item_3();
    test_heap_init_sized_1();
    test_heap_init_sized_2();
    test_heap_init_sized_3();
    test_heap_parent_index_1();
    test_heap_parent_index_2();
    test_heap_pop_1();
    test_heap_pop_2();
    test_heap_pop_3();
    test_heap_left_child_index_1();
    test_heap_right_child_index_1();
    test_heap_sift_down_1();
    test_heap_sift_up_1();
    test_heap_swap_items_1();
    test_heap_swap_items_2();
    test_heap_swap_items_3();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
