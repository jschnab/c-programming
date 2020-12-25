#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "hashmap.h"


HMItem HM_DELETED_ITEM = {NULL, NULL, 0};
static const int HM_PRIME_1 = 151;
static const int HM_PRIME_2 = 163;
static const int HM_BASE_SIZE = 50;


void *hm_copy_value(void *source, char type) {
    void *target;
    switch (type) {
        case INT:
            target = malloc(sizeof(int));
            if (target == NULL) {
                fprintf(stderr, "error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, sizeof(int));
            break;
        case FLOAT:
            target = malloc(sizeof(float));
            if (target == NULL) {
                fprintf(stderr, "error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, sizeof(float));
            break;
        case STRING:
            target = malloc(strlen(source));
            if (target == NULL) {
                fprintf(stderr, "error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, strlen(source));
            break;
        default:
            fprintf(stderr, "error: data type not supported");
            exit(1);
    }
    return target;
}


HMItem *hm_create_item(char *key, void *value, char value_type) {
    HMItem *item = malloc(sizeof(HMItem));
    item->key = strdup(key);
    item->value = hm_copy_value(value, value_type);
    item->type = value_type;
    return item;
}


void hm_delete(HashMap *map, char *key) {
    /* eventually resize HashMap */
    int load = map->count * 100 / map->size;
    if (load < 10)
        hm_resize_down(map);

    int index = hm_get_hash(key, map->size, 0);
    HMItem *item = map->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HM_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                hm_delete_item(item);
                map->items[index] = &HM_DELETED_ITEM;
            }
        }
        index = hm_get_hash(key, map->size, i);
        item = map->items[index];
        i++;
    }
    map->count--;
}


void hm_delete_hashmap(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        HMItem *item = map->items[i];
        if (item != NULL && item != &HM_DELETED_ITEM) {
            hm_delete_item(item);
        }
    }
    free(map->items);
    free(map);
}


void hm_delete_item(HMItem *item) {
    free(item->key);
    free(item->value);
    free(item);
}


int hm_get_hash(char *key, int size, int attempt) {
    int hash_a = hm_hash(key, HM_PRIME_1, size);
    int hash_b = hm_hash(key, HM_PRIME_2, size);
    return (hash_a + (attempt * (hash_b + 1))) % size;
}


int hm_hash(char *key, int prime, int size) {
    long hash = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i ++)
        hash += (long) pow(prime, len - i - 1) * key[i];
    hash %= size;
    return (int) hash;
}


/* API function to create an empty HashMap */
HashMap *hm_init() {
    return hm_init_sized(HM_BASE_SIZE);
}


/* helper function to initialize a HashMap with at least a certain size */
HashMap *hm_init_sized(int base_size) {
    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) {
        fprintf(stderr, "error: can't allocate memory to create HashMap");
        exit(1);
    }
    map->base_size = base_size;
    map->size = hm_next_prime(map->base_size);
    map->count = 0;
    map->items = calloc((size_t)map->size, sizeof(HMItem));
    if (map->items == NULL) {
        fprintf(stderr, "error: can't allocate memory for HashMap items");
        exit(1);
    }
    return map;
}


/* insert a key-value pair into a HashMap */
void hm_insert(HashMap *map, char *key, void *value, char value_type) {
    /* eventually resize HashMap */
    int load = map->count * 100 / map->size;
    if (load > 70)
        hm_resize_up(map);

    HMItem *item = hm_create_item(key, value, value_type);
    int index = hm_get_hash(item->key, map->size, 0);
    HMItem *current = map->items[index];
    int i = 1;
    while (current != NULL) {
        if (current != &HM_DELETED_ITEM) {
            if (strcmp(current->key, key) == 0) {
                hm_delete_item(current);
                map->items[index] = item;
                return;
            }
        }
        index = hm_get_hash(item->key, map->size, i);
        current = map->items[index];
        i++;
    }
    map->items[index] = item;
    map->count += 1;
}


/* returns whether x is a prime number or not:
 *  1 - prime
 *  0 - not prime
 * -1 - undefined (i.e. x < 2) */
int hm_is_prime(int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if (x % 2 == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double)x)); i += 2)
        if (x % i == 0)
            return 0;
    return 1;
}


/* returns the next prime number after x, or x if x is prime */
int hm_next_prime(int x) {
    while (hm_is_prime(x) != 1)
        x++;
    return x;
}


/* resize the HashMap when it's growing too large or shrinking too small */
void hm_resize(HashMap *map, int base_size) {
    if (base_size < HM_BASE_SIZE)
        return;

    /* copy items in new map having the desired size */
    HashMap *new_map = hm_init_sized(base_size);
    for (int i = 0; i < map->size; i++) {
        HMItem *item = map->items[i];
        if (item != NULL && item != &HM_DELETED_ITEM)
            hm_insert(new_map, item->key, item->value, item->type);
    }

    /* set attributes of old map with attributes of new map */
    map->base_size = new_map->base_size;
    map->count = new_map->count;

    /* swap sizes */
    int tmp_size = map->size;
    map->size = new_map->size;
    new_map->size = tmp_size;

    /* swap items */
    HMItem **tmp_items = map->items;
    map->items = new_map->items;
    new_map->items = tmp_items;

    hm_delete_hashmap(new_map);
}


/* convenience function to shrink a HashMap */
void hm_resize_down(HashMap *map) {
    int new_size = map->base_size / 2;
    hm_resize(map, new_size);
}


/* convenience function to grow a HashMap */
void hm_resize_up(HashMap *map) {
    int new_size = map->base_size * 2;
    hm_resize(map, new_size);
}


/* look for an item with a given key in a HashMap */
void *hm_search(HashMap *map, char *key) {
    int index = hm_get_hash(key, map->size, 0);
    HMItem *item = map->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HM_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = hm_get_hash(key, map->size, i);
        item = map->items[index];
        i++;
    }
    return NULL;
}
