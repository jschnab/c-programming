#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_types.h"
#include "../hashset.h"


extern char *HS_DELETED_ITEM;
static int n_fail;


/* add a string to a set */
void test_hs_add_1() {
    HashSet *set = hs_init();
    char *item = "cat";
    hs_add(set, item);
    if (set->count != 1 || strcmp(set->items[5], item) != 0) {
        n_fail++;
        printf("test_hs_add_1: FAILED\n");
        return;
    }
    printf("test_hs_add_1: PASS\n");
}


/* add same item to set after discarding */
void test_hs_add_2() {
    HashSet *set = hs_init();
    char *item = "cat";
    hs_add(set, item);
    hs_discard(set, item);
    hs_add(set, item);
    if (
        set->count != 1 ||
        strcmp(set->items[5], item) != 0 ||
        set->items[5] == HS_DELETED_ITEM
    ) {
        n_fail++;
        printf("test_hs_add_2: FAILED\n");
        return;
    }
    printf("test_hs_add_2: PASS\n");
}


/* delete an empty set */
void test_hs_delete_1() {
    HashSet *set = hs_init();
    hs_delete_set(set);
    printf("test_hs_delete_1: PASS\n");
}


/* delete a set with 1 element */
void test_hs_delete_2() {
    HashSet *set = hs_init();
    hs_add(set, "cat");
    hs_delete_set(set);
    printf("test_hs_delete_2: PASS\n");
}


/* delete from set containing 1 item */
void test_hs_discard_1() {
    HashSet *set = hs_init();
    char *item = "cat";
    hs_add(set, item);
    hs_discard(set, item);
    if (set->count != 0 || set->items[5] != HS_DELETED_ITEM) {
        n_fail++;
        printf("test_hs_discard_1: FAILED\n");
        return;
    }
    printf("test_hs_discard_1: PASS\n");
}


/* get hash of string on 1st attempt */
void test_hs_get_hash_1() {
    if (hs_get_hash("cat", 53, 0) != 5) {
        n_fail++;
        printf("test_hs_get_hash_1: FAILED\n");
        return;
    }
    printf("test_hs_get_hash_1: PASS\n");
}


/* get hash of string on 2nd attempt */
void test_hs_get_hash_2() {
    if (hs_get_hash("cat", 53, 1) != 27) {
        n_fail++;
        printf("test_hs_get_hash_2: FAILED\n");
        return;
    }
    printf("test_hs_get_hash_2: PASS\n");
}


/* hash a string */
void test_hs_hash_1() {
    if (hs_hash("cat", 151, 53) != 5) {
        n_fail++;
        printf("test_hs_hash_1: FAILED\n");
        return;
    }
    printf("test_hs_hash_1: PASS\n");
}


/* test helper function for initialization of hashset */
void test_hs_init_sized_1() {
    HashSet *set = hs_init_sized(10);
    if (set->base_size != 10 || set->size != 11 || set->count != 0) {
        n_fail++;
        printf("test_hs_init_sized_1: FAILED\n");
        return;
    }
    printf("test_hs_init_sized_1: PASS\n");
}


/* test initialization of hashmap */
void test_hs_init_1() {
    HashSet *set = hs_init();
    if (set->base_size != 50 || set->size != 53 || set->count != 0) {
        n_fail++;
        printf("test_hs_init_1: FAILED\n");
        return;
    }
    printf("test_hs_init_1: PASS\n");
}


/* test if first 25 prime numbers are identified as such */
void test_hs_is_prime_1() {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < 25; i++) {
        if (hs_is_prime(primes[i]) != 1) {
            n_fail++;
            printf("test_hs_is_prime_1: FAILED\n");
            return;
        }
    }
    printf("test_hs_is_prime_1: PASS\n");
}


/* test if first few non-prime numbers are identified as such */
void test_hs_is_prime_2() {
    int non_primes[] = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27};
    for (int i = 0; i < 17; i++) {
        if (hs_is_prime(non_primes[i]) != 0) {
            n_fail++;
            printf("test_hs_is_prime_2: FAILED\n");
            return;
        }
    }
    printf("test_hs_is_prime_2: PASS\n");
}


/* test if undefined numbers are identified as such */
void test_hs_is_prime_3() {
    if (hs_is_prime(0) != -1 || hs_is_prime(1) != -1) {
        n_fail++;
        printf("test_hs_is_prime_3: FAILED\n");
        return;
    }
    printf("test_hs_is_prime_3: PASS\n");
}


/* get next prime for number < 2 */
void test_hs_next_prime_1() {
    if (hs_next_prime(0) != 2 || hs_next_prime(1) != 2) {
        n_fail++;
        printf("test_hs_next_prime_1: FAILED\n");
        return;
    }
    printf("test_hs_next_prime_1: PASS\n");
}


/* get next prime for number > 2 */
void test_hs_next_prime_2() {
    if (
        hs_next_prime(10) != 11 ||
        hs_next_prime(20) != 23 ||
        hs_next_prime(30) != 31 ||
        hs_next_prime(40) != 41 ||
        hs_next_prime(50) != 53 ||
        hs_next_prime(60) != 61 ||
        hs_next_prime(70) != 71 ||
        hs_next_prime(80) != 83 ||
        hs_next_prime(90) != 97
    ) {
        n_fail++;
        printf("test_hs_next_prime_2: FAILED\n");
        return;
    }
    printf("test_hs_next_prime_2: PASS\n");
}


/* resize up a HashSet */
void test_hs_resize_1() {
    HashSet *set = hs_init();
    char *items[] = {"cat", "hat"};
    int base_size = 60; /* size after resizing */
    int indices[] = {56, 52};  /* expected indices in set after resize */
    int i;
    for (i = 0; i < 2; i++) {
        hs_add(set, items[i]);
    }
    hs_resize(set, base_size);
    if (set->base_size != base_size || set->size != 61 || set->count != 2) {
        n_fail++;
        printf("test_hs_resize_1: FAILED\n");
        return;
    }
    for (i = 0; i < 2; i++) {
        if (strcmp(set->items[indices[i]], items[i]) != 0) {
            n_fail++;
            printf("test_hs_resize_1: FAILED\n");
            return;
        }
    }
    printf("test_hs_resize_1: PASS\n");
}


/* resize down a HashSet */
void test_hs_resize_2() {
    HashSet *set = hs_init_sized(60);
    char *items[] = {"cat", "hat"};
    int base_size = 50;  /* size after resizing */
    int indices[] = {5, 7};  /* expected indices in set after resize */
    int i;
    for (i = 0; i < 2; i++) {
        hs_add(set, items[i]);
    }
    hs_resize(set, base_size);
    if (set->base_size != base_size || set->size != 53 || set->count != 2) {
        n_fail++;
        printf("test_hs_resize_2: FAILED\n");
        return;
    }
    for (i = 0; i < 2; i++) {
        if (set->items[indices[i]] != items[i]) {
            n_fail++;
            printf("test_hs_resize_2: FAILED\n");
            return;
        }
    }
    printf("test_hs_resize_2: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running unit tests for hashset...\n\n");
    test_hs_add_1();
    test_hs_add_2();
    test_hs_delete_1();
    test_hs_delete_2();
    test_hs_discard_1();
    test_hs_get_hash_1();
    test_hs_get_hash_2();
    test_hs_hash_1();
    test_hs_init_sized_1();
    test_hs_init_1();
    test_hs_is_prime_1();
    test_hs_is_prime_2();
    test_hs_is_prime_3();
    test_hs_next_prime_1();
    test_hs_next_prime_2();
    test_hs_resize_1();
    test_hs_resize_2();
    printf("\nFinished tests\nNumber of failures: %d\n", n_fail);
}
