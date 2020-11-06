#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_types.h"
#include "../hashmap.h"


static int n_fail;


/* test initialization of hashmap */
void test_hm_init_1() {
    HashMap *map = hm_init();
    if (map->size != 53 || map->count != 0) {
        n_fail++;
        printf("test_hm_init_1: FAILED\n");
        return;
    }
    printf("test_hm_init_1: PASS\n");
}


/* test copy integer value */
void test_hm_copy_value_1() {
    int value = 3;
    void *copy = hm_copy_value(&value, INT);
    if (*(int *)copy != value) {
        n_fail++;
        printf("test_hm_copy_value_1: FAILED\n");
        return;
    }
    printf("test_hm_copy_value_1: PASS\n");
}


/* test copy float value */
void test_hm_copy_value_2() {
    float value = 5.0;
    void *copy = hm_copy_value(&value, FLOAT);
    if (*(float *)copy != value) {
        n_fail++;
        printf("test_hm_copy_value_2: FAILED\n");
        return;
    }
    printf("test_hm_copy_value_2: PASS\n");
}


/* test copy string value */
void test_hm_copy_value_3() {
    char *value = "hello";
    void *copy = hm_copy_value(value, STRING);
    if (strcmp(value, copy) != 0) {
        n_fail++;
        printf("test_hm_copy_value_3: FAILED\n");
        return;
    }
    printf("test_hm_copy_value_3: PASS\n");
}


void test_hm_create_item_1() {
    char *key = "hello";
    float value = 3.14;
    HMItem *pair = hm_create_item(key, &value, STRING, FLOAT);
    if (strcmp(pair->key, key) != 0 || *(float *)pair->value != value) {
        n_fail++;
        printf("test_hm_create_item_1: FAILED\n");
        return;
    }
    printf("test_hm_create_item_1: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for hashmap...\n\n");
    test_hm_init_1();
    test_hm_copy_value_1();
    test_hm_copy_value_2();
    test_hm_copy_value_3();
    test_hm_create_item_1();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
