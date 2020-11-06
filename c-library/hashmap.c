#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "hashmap.h"


HashMap *hm_init() {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = 53;
    map->count = 0;
    map->items = calloc((size_t)map->size, sizeof(HMItem));
    return map;
}


void *hm_copy_value(void *source, char type) {
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


HMItem *hm_create_item(void *key, void *value, char key_type, char value_type) {
    HMItem *item = malloc(sizeof(HMItem));
    item->key = hm_copy_value(key, key_type);
    item->value = hm_copy_value(value, value_type);
    return item;
}
