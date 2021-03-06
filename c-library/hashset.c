#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "hashset.h"


char *HS_DELETED_ITEM;
static const int HS_PRIME_1 = 151;
static const int HS_PRIME_2 = 163;
static const int HS_BASE_SIZE = 50;


/* add a value into a HashSet */
void hs_add(HashSet *set, char *value) {
    /* eventually resize HashSet */
    int load = set->count * 100 / set->size;
    if (load > 70) {
        hs_resize_up(set);
    }

    int index = hs_get_hash(value, set->size, 0);
    char *current = set->items[index];
    int attempt = 1;
    while (current != NULL && current != HS_DELETED_ITEM) {
        /* do nothing if value already in the set */
        if (strcmp(current, value) == 0) {
            return;
        }
        index = hs_get_hash(current, set->size, attempt);
        current = set->items[index];
        attempt++;
    }
    set->items[index] = value;
    set->count++;
}


/* delete a HashSet */
void hs_delete_set(HashSet *set) {
    free(set->items);
    free(set);
}


/* return difference between two sets */
HashSet *hs_difference(HashSet *x, HashSet *y) {
    HashSet *result = hs_init();
    for (int i = 0; i < x->size; i++) {
        if (x->items[i] != NULL && hs_search(y, x->items[i]) == 0)
            hs_add(result, x->items[i]);
    }
    return result;
}


void hs_discard(HashSet *set, char *value) {
    /* eventually resize HashSet */
    int load = set->count / set->size * 100;
    if (load < 20) {
        hs_resize_down(set);
    }

    int index = hs_get_hash(value, set->size, 0);
    char *item = set->items[index];
    int attempt = 1;
    while (item != NULL) {
        if (item != HS_DELETED_ITEM) {
            if (strcmp(item, value) == 0) {
                set->items[index] = HS_DELETED_ITEM;
            }
        }
        index = hs_get_hash(value, set->size, attempt);
        item = set->items[index];
        attempt++;
    }
    set->count--;
}


/* return 1 if two sets are disjoint, else 0 */
int hs_disjoint(HashSet * x, HashSet * y) {
    if (x->count == 0 || y->count == 0)
        return 1;
    if (x->count > y->count) {
        HashSet *tmp = x;
        x = y;
        y = tmp;
    }
    for (int i = 0; i < x->size; i++) {
        if (x->items[i] != NULL && hs_search(y, x->items[i]) == 1)
            return 0;
    }
    return 1;
}


int hs_get_hash(char *value, int size, int attempt) {
    int hash_a = hs_hash(value, HS_PRIME_1, size);
    int hash_b = hs_hash(value, HS_PRIME_2, size);
    return (hash_a + (attempt * (hash_b + 1))) % size;
}


int hs_hash(char *value, int prime, int size) {
    long hash = 0;
    int len = strlen(value);
    for (int i = 0; i < len; i++) {
        hash += (long) pow(prime, len - i - 1) * value[i];
    }
    hash %= size;
    return (int) hash;
}


/* create an empty HashSet */
HashSet *hs_init() {
    return hs_init_sized(HS_BASE_SIZE);
}


/* helper function to initialize a HashSet with at least a certain size */
HashSet *hs_init_sized(int base_size) {
    HashSet *set = (HashSet *) malloc(sizeof(HashSet));
    if (set == NULL) {
        fprintf(stderr, "error: can't allocate memory to create HashSet");
        exit(1);
    }
    set->base_size = base_size;
    set->size = hs_next_prime(set->base_size);
    set->count = 0;
    set->items = calloc((size_t)set->size, sizeof(char *));
    if (set->items == NULL) {
        fprintf(stderr, "error: can't allocate memory for HashSet items");
        exit(1);
    }
    return set;
}


/* return the intersection of two sets */
HashSet *hs_intersection(HashSet *x, HashSet *y) {
    HashSet *result = hs_init();
    if (x->count > y->count) {
        HashSet *tmp = x;
        x = y;
        y = tmp;
    }
    for (int i = 0; i < x->size; i++) {
        if (x->items[i] != NULL && hs_search(y, x->items[i]) != 0)
            hs_add(result, x->items[i]);
    }
    return result;
}


/* returns whether x is a prime number or not:
 *  1 - prime
 *  0 - not prime
 * -1 - undefined (i.e. x < 2) */
int hs_is_prime(int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if (x % 2 == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double)x)); i += 2)
        if (x % i == 0)
            return 0;
    return 1;
}


/* returns the next prime number after x, or x if x is prime */
int hs_next_prime(int x) {
    while (hs_is_prime(x) != 1)
        x++;
    return x;
}


/* resize the HashSet when it's growing too large or shrinking too small */
void hs_resize(HashSet *set, int base_size) {
    if (base_size < HS_BASE_SIZE)
        return;

    /* copy items in new set having the desired size */
    HashSet *new_set = hs_init_sized(base_size);
    for (int i = 0; i < set->size; i++) {
        char *item = set->items[i];
        if (item != NULL && item != HS_DELETED_ITEM)
            hs_add(new_set, item);
    }

    /* set attributes of old set with attributes of new set */
    set->base_size = new_set->base_size;
    set->count = new_set->count;

    /* swap sizes */
    int tmp_size = set->size;
    set->size = new_set->size;
    new_set->size = tmp_size;

    /* swap items */
    char ** tmp_items = set->items;
    set->items = new_set->items;
    new_set->items = tmp_items;

    hs_delete_set(new_set);
}


/* convenience function to shrink a HashSet */
void hs_resize_down(HashSet *set) {
    int new_size = set->base_size / 2;
    hs_resize(set, new_size);
}


/* convenience function to grow a HashSet */
void hs_resize_up(HashSet *set) {
    int new_size = set->base_size * 2;
    hs_resize(set, new_size);
}


/* look for a given value in a HashSet and returns:
 * 1 - the value is in the set
 * 0 - the value is not in the set */
int hs_search(HashSet *set, char *value) {
    int index = hs_get_hash(value, set->size, 0);
    char *item = set->items[index];
    int attempt = 1;
    while (item != NULL) {
        if (item != HS_DELETED_ITEM) {
            if (strcmp(item, value) == 0) {
                return 1;
            }
        }
        index = hs_get_hash(value, set->size, attempt);
        item = set->items[index];
        attempt++;
    }
    return 0;
}


/* return 1 if x is a subset of y, else 0 */
int hs_subset(HashSet *x, HashSet *y) {
    if (x->count == 0)
        return 1;
    if (x->count > y->count)
        return 0;
    for (int i = 0; i < x->size; i++) {
        if (x->items[i] != NULL && hs_search(y, x->items[i]) != 1)
            return 0;
    }
    return 1;
}


/* return 1 if x is a superset of y, else 0 */
int hs_superset(HashSet *x, HashSet *y) {
    return hs_subset(y, x);
}


/* return the union of sets x and y */
HashSet *hs_union(HashSet *x, HashSet *y) {
    HashSet *result = hs_init();
    int i;
    for (i = 0; i < x->size; i++)
        if (x->items[i] != NULL)
            hs_add(result, x->items[i]);
    for (i = 0; i < y->size; i++)
        if (y->items[i] != NULL)
            hs_add(result, y->items[i]);
    return result;
}
