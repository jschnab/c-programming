#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "hashmap.h"


static HMItem HM_DELETED_ITEM = {NULL, NULL);


HashMap *hm_init() {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = 53;
    map->count = 0;
    map->items = calloc((size_t)map->size, sizeof(HMItem));
    return map;
}


void *hm_copy_value(void *source, char type) {
    void *target;
    switch (type) {
        case INT:
            target = malloc(sizeof(int));
            if (target == NULL) {
                printf("error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, sizeof(type));
            break;
        case FLOAT:
            target = malloc(sizeof(float));
            if (target == NULL) {
                printf("error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, sizeof(float));
            break;
        case STRING:
            target = malloc(strlen(source));
            if (target == NULL) {
                printf("error: can't allocate memory to copy pointer value");
                exit(1);
            }
            memcpy(target, source, strlen(source));
            break;
        default:
            printf("error: data type not supported");
            exit(1);
    }
    return target;
}


HMItem *hm_create_item(char *key, void *value, char value_type) {
    HMItem *item = malloc(sizeof(HMItem));
    item->key = strdup(key);
    item->value = hm_copy_value(value, value_type);
    return item;
}


void hm_delete(HashMap *map, char *key) {
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
        if (item != NULL) {
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
        hash += (long) pow(prime, len - i + 1) * key[i];
    hash %= size;
    return (int) hash;
}


void hm_insert(HashMap *map, char *key, void *value, char value_type) {
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
        index = hm_get_hash(item->key, map_size, i);
        current = map->items[index];
        i++;
    }
    map->items[index] = item;
    map->count += 1;
}


void *hm_search(HashMap *map, char *key) {
    int index = hm_get_hash(key, map->size, 0);
    HMItem *item = map->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HM_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0)
                return item->value;
        }
        index = hm_get_hash(key, map->size, i);
        item = map->items[index];
        i++;
    }
    return NULL;
}
