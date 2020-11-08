#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_types.h"
#include "../hashmap.h"

/* marking extern to avoid problems when putting this variable in hashmap.h */
extern HMItem HM_DELETED_ITEM; 
static int n_fail;


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


/* create an item storing a float value */
void test_hm_create_item_1() {
    char *key = "hello";
    float value = 3.14;
    HMItem *pair = hm_create_item(key, &value, FLOAT);
    if (pair->type != FLOAT || strcmp(pair->key, key) != 0 || *(float *)pair->value != value) {
        n_fail++;
        printf("test_hm_create_item_1: FAILED\n");
        return;
    }
    printf("test_hm_create_item_1: PASS\n");
}


/* delete from hashmap with 1 item*/
void test_hm_delete_1() {
    HashMap *map = hm_init();
    char *key = "cat";
    int value = 7;
    hm_insert(map, key, &value, INT);
    hm_delete(map, key);
    if (map->count != 0 || map->items[5] != &HM_DELETED_ITEM) {
        n_fail++;
        return;
    }
    printf("test_hm_delete_1: PASS\n");
}


/* get hash of string on 1st attempt*/
void test_hm_get_hash_1() {
    int hash = hm_get_hash("cat", 53, 0);
    if (hash != 5) {
        n_fail++;
        printf("test_hm_get_hash_1: FAILED\n");
        return;
    }
    printf("test_hm_get_hash_1: PASS\n");
}


/* get hash of string on second attempt*/
void test_hm_get_hash_2() {
    int hash = hm_get_hash("cat", 53, 1);
    if (hash != 27) {
        n_fail++;
        printf("test_hm_get_hash_2: FAILED\n");
        return;
    }
    printf("test_hm_get_hash_2: PASS\n");
}


/* hash a string */
void test_hm_hash_1() {
    int hash = hm_hash("cat", 151, 53);
    if (hash != 5) {
        n_fail++;
        printf("test_hm_hash_1: FAILED\n");
        return;
    }
    printf("test_hm_hash_1: PASS\n");
}


/* test initialization of hashmap */
void test_hm_init_1() {
    HashMap *map = hm_init();
    if (map->base_size != 50 || map->size != 53 || map->count != 0) {
        n_fail++;
        printf("test_hm_init_1: FAILED\n");
        return;
    }
    printf("test_hm_init_1: PASS\n");
}


/* test helper function for initialization of hashmap */
void test_hm_init_sized_1() {
    HashMap *map = hm_init_sized(10);
    if (map->base_size != 10 || map->size != 11 || map->count != 0) {
        n_fail++;
        printf("test_hm_init_sized_1: FAILED\n");
        return;
    }
    printf("test_hm_init_sized_1: PASS\n");

}


/* test if first 25 prime numbers are identified as such */
void test_hm_is_prime_1() {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < 25; i++) {
        if (hm_is_prime(primes[i]) != 1) {
            n_fail++;
            printf("test_hm_is_prime_1: FAILED\n");
            return;
        }
    }
    printf("test_hm_is_prime_1: PASS\n");
}


/* test if first few non-prime numbers are identified as such */
void test_hm_is_prime_2() {
    int not_primes[] = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27};
    for (int i = 0; i < 17; i++) {
        if (hm_is_prime(not_primes[i]) != 0) {
            n_fail++;
            printf("test_hm_is_prime_2: FAILED\n");
            return;
        }
    }
    printf("test_hm_is_prime_2: PASS\n");
}


/* test if undefined numbers are identified as such */
void test_hm_is_prime_3() {
    int undef[] = {0, 1};
    for (int i = 0; i < 2; i++) {
        if (hm_is_prime(undef[i]) != -1) {
            n_fail++;
            printf("test_hm_is_prime_3: FAILED\n");
            return;
        }
    }
    printf("test_hm_is_prime_3: PASS\n");
}


/* insert item with integer value in hashmap */
void test_hm_insert_1() {
    HashMap *map = hm_init();
    char *key = "cat";
    int value = 7;
    hm_insert(map, key, &value, INT);
    HMItem *item = map->items[5];
    if (map->count != 1 || strcmp(item->key, key) != 0 || *(int *)item->value != value) {
        n_fail++;
        printf("test_hm_insert_1: FAILED\n");
        return;
    }
    printf("test_hm_insert_1: PASS\n");
}


/* get next prime number < 2*/
void test_hm_next_prime_1() {
    if (hm_next_prime(0) != 2 || hm_next_prime(1) != 2) {
        n_fail++;
        printf("test_hm_next_prime_1: FAILED\n");
        return;
    }
    printf("test_hm_next_prime_1: PASS\n");
}


/* get next prime number > 2*/
void test_hm_next_prime_2() {
    if (
        hm_next_prime(10) != 11 ||
        hm_next_prime(20) != 23 ||
        hm_next_prime(30) != 31 ||
        hm_next_prime(40) != 41 ||
        hm_next_prime(50) != 53 ||
        hm_next_prime(60) != 61 ||
        hm_next_prime(70) != 71 ||
        hm_next_prime(80) != 83 ||
        hm_next_prime(90) != 97
    ) {
        n_fail++;
        printf("test_hm_next_prime_2: FAILED\n");
        return;
    }
    printf("test_hm_next_prime_2: PASS\n");
}


/* resize up a HashMap */
void test_hm_resize_1() {
    HashMap *map = hm_init();
    char *keys[] = {"cat", "hat"};
    int values[] = {99, 11};
    int base_size = 60;
    int indices[] = {56, 52};  /* expected indices in map after resize */
    int i;
    for (i = 0; i < 2; i++)
        hm_insert(map, keys[i], &values[i], INT);
    hm_resize(map, base_size);
    if (
        map->base_size != 60 ||
        map->size != 61 ||
        map->count != 2
    ) {
        n_fail++;
        printf("test_hm_resize_1: FAILED\n");
        return;
    }
    for (i = 0; i < 2; i++) {
        if (*(int *)map->items[indices[i]]->value != values[i]) {
            n_fail++;
            printf("test_hm_resize_1: FAILED\n");
            return;
        }
    }
    printf("test_hm_resize_1; PASS\n");
    hm_delete_hashmap(map);
}


/* search item with integer value in hashmap */
void test_hm_search_1() {
    HashMap *map = hm_init();
    char *key = "cat";
    int value = 7;
    hm_insert(map, key, &value, INT);
    int found = *(int *)hm_search(map, key);
    if (found != value) {
        n_fail++;
        printf("test_hm_search_1: FAILED\n");
        return;
    }
    printf("test_hm_search_1: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for hashmap...\n\n");
    test_hm_copy_value_1();
    test_hm_copy_value_2();
    test_hm_copy_value_3();
    test_hm_create_item_1();
    test_hm_delete_1();
    test_hm_get_hash_1();
    test_hm_get_hash_2();
    test_hm_hash_1();
    test_hm_init_1();
    test_hm_init_sized_1();
    test_hm_is_prime_1();
    test_hm_is_prime_2();
    test_hm_is_prime_3();
    test_hm_insert_1();
    test_hm_next_prime_1();
    test_hm_next_prime_2();
    test_hm_resize_1();
    test_hm_search_1();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
