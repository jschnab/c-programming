#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "data_types.h"

int BASE_SIZE = 30;


/* append an item to the array
 * this function assumes the caller knows the type of the array and will
 * append an element of the correct type */
void darray_append(DArray *array, void *value) {
    /* eventually grow array if full */
    if (array->count == array->size) {
        darray_resize_up(array);
    }
    char *str;
    switch (array->type) {
        case INT:
            ((int *)array->items)[array->count] = *(int *)value;
            break;
        case FLOAT:
            ((float *)array->items)[array->count] = *(float *)value;
            break;
        case STRING:
            str = (char *)malloc(strlen((char *)value)+1);
            if (str == NULL) {
                fprintf(stderr, "error: can't allocate memory for array item\n");
                exit(1);
            }
            strcpy(str, (char *)value);
            ((char **)array->items)[array->count] = str;
            break;
        default:
            fprintf(stderr, "error: array type not supported\n");
            exit(1);
    }
    array->count++;
}


/* compare two array items A and B based on their indices a and b, return:
 *  0: items have the same value
 * -1: item A < item B
 *  1: item A > item B */
int darray_compare_items(DArray *array, int a, int b) {
    int i1, i2;
    float f1, f2;
    char *s1, *s2;
    int comp;
    switch (array->type) {
        case INT:
            i1 = ((int *)array->items)[a];
            i2 = ((int *)array->items)[b];
            if (i1 > i2)
                return 1;
            if (i1 < i2)
                return -1;
            else
                return 0;
        case FLOAT:
            f1 = ((float *)array->items)[a];
            f2 = ((float *)array->items)[b];
            if (f1 > f2)
                return 1;
            if (f1 < f2)
                return -1;
            else
                return 0;
        case STRING:
            s1 = ((char **)array->items)[a];
            s2 = ((char **)array->items)[b];
            comp = strcmp(s1, s2);
            if (comp > 0)
                return 1;
            if (comp < 0)
                return -1;
            else
                return 0;
        default:
            fprintf(stderr, "error: array type not supported\n");
            exit(1);
    }
}


/* delete a dynamic array */
void darray_delete(DArray *array) {
    if (array->type == STRING) {
        for (int i = 0; i < array->count; i++) {
            free(((char **)array->items)[i]);
        }
    }
    free(array->items);
    free(array);
}


/* delete an item from the array at the specified index*/
void darray_delete_item(DArray *array, int index) {
    switch (array->type) {
        case INT:
            ((int *)array->items)[index] = 0;
            break;
        case FLOAT:
            ((float *)array->items)[index] = 0.0;
            break;
        case STRING:
            free(((char **)array->items)[index]);
            break;
    }
    array->count--;
    /* eventually shrink array if sparse*/
    if (array->count < array->size / 2) {
        darray_resize_down(array);
    }
}


/* initialized an empty array of a given type
 * wrapper around darray_init_sized() */
DArray *darray_init(char type) {
    return darray_init_sized(type, BASE_SIZE);
}


/* initializes an empty array of a given type and size */
DArray *darray_init_sized(char type, int size) {
    DArray *array = (DArray *)malloc(sizeof(DArray));
    if (array == NULL) {
        fprintf(stderr, "error: can't allocate memory for dynamic array\n");
        exit(1);
    }
    switch (type) {
        case INT:
            array->items = calloc((size_t)size, sizeof(int));
            break;
        case FLOAT:
            array->items = calloc((size_t)size, sizeof(float));
            break;
        case STRING:
            array->items = calloc((size_t)size, sizeof(char *));
            break;
        default:
            fprintf(stderr, "error: can't allocate memory for dynamic array\n");
            exit(1);
    }
    if (array->items == NULL) {
        fprintf(stderr, "error: can't allocat memory for dynamic array items\n");
        exit(1);
    }
    array->type = type;
    array->size = size;
    array->count = 0;
    return array;
}


/* remove the last element from the array, create a new pointer to its value
 * and return it */
void *darray_pop(DArray *array) {
    int last = array->count - 1;
    void *result = NULL;
    char *to_pop;
    switch (array->type) {
        case INT:
            result = malloc(sizeof(int));
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for poped array item");
                exit(1);
            }
            *(int *)result = ((int *)array->items)[last];
            break;
        case FLOAT:
            result = malloc(sizeof(float));
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for poped array item");
                exit(1);
            }
            *(float *)result = ((float *)array->items)[last];
            break;
        case STRING:
            to_pop = ((char **)array->items)[last];
            result = malloc(strlen(to_pop)+1);
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for poped array item");
                exit(1);
            }
            strcpy((char *)result, to_pop);
            break;
    }
    darray_delete_item(array, last);
    return result;
}


/* sort the array in place using quicksort */
void darray_quicksort(DArray *array, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = left;
    for (int i = left; i < right; i++) {
        if (darray_compare_items(array, i, right) < 0) {
            darray_swap_items(array, i, pivot);
            pivot++;
        }
    }
    darray_swap_items(array, pivot, right);
    darray_quicksort(array, left, pivot-1);
    darray_quicksort(array, pivot+1, right);
}


/* resize the array */
void darray_resize(DArray *array, int new_size) {
    if (new_size < BASE_SIZE) {
        return;
    }
    switch (array->type) {
        case INT:
            array->items = realloc(array->items, sizeof(int) * (size_t)new_size);
            break;
        case FLOAT:
            array->items = realloc(array->items, sizeof(float) * (size_t)new_size);
            break;
        case STRING:
            array->items = realloc(array->items, sizeof(char *) * (size_t)new_size);
            break;
        default:
            fprintf(stderr, "error: array type not supported\n");
            exit(1);
    }
    if (array->items == NULL) {
        fprintf(stderr, "error: can't allocate memory for dynamic array\n");
        exit(1);
    }
    array->size = new_size;
}


/* increase the size of the array */
void darray_resize_up(DArray *array) {
    darray_resize(array, array->size * 2);
}


/* decrease the size of the array */
void darray_resize_down(DArray *array) {
    darray_resize(array, array->size / 2);
}


/* swap two array items */
void darray_swap_items(DArray *array, int i, int j) {
    int int_tmp;
    float float_tmp;
    char *str_tmp;
    switch (array->type) {
        case INT:
            int_tmp = ((int *)array->items)[i];
            ((int *)array->items)[i] = ((int *)array->items)[j];
            ((int *)array->items)[j] = int_tmp;
            break;
        case FLOAT:
            float_tmp = ((float *)array->items)[i];
            ((float *)array->items)[i] = ((float *)array->items)[j];
            ((float *)array->items)[j] = float_tmp;
            break;
        case STRING:
            str_tmp = ((char **)array->items)[i];
            ((char **)array->items)[i] = ((char **)array->items)[j];
            ((char **)array->items)[j] = str_tmp;
            break;
        default:
            fprintf(stderr, "error: dynamic array type not supported\n");
            exit(1);
    }
}
