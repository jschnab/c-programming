#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_types.h"
#include "heap.h"


static const int BASE_SIZE = 30;


/* add item to the heap */
void heap_add(Heap *heap, void *value) {
    /* eventually resize the heap */
    if (heap->count == heap->size)
        heap_resize_up(heap);

    char *new;
    switch (heap->type) {
        case INT:
            ((int *)heap->items)[heap->count] = *(int *)value;
            break;
        case FLOAT:
            ((float *)heap->items)[heap->count] = *(float *)value;
            break;
        case STRING:
            new = (char *)malloc(strlen((char *)value)+1);
            if (new == NULL) {
                fprintf(stderr, "error: can't allocate memory for heap item\n");
                exit(1);
            }
            strcpy(new, (char *)value);
            ((char **)heap->items)[heap->count] = new;
            break;
        default:
            fprintf(stderr, "error: supported heap item type\n");
            exit(1);
    }
    heap_sift_up(heap, heap->count);
    heap->count++;
}


/* compare the value of two heap items, identified by their indices a and b
 * returns an integer:
 *  0 if values are equal
 *  1 if value of A > B
 * -1 if value of A < B
 * Important: this function assumes items have the same type */
int heap_compare_items(Heap *heap, int a, int b) {
    int i1, i2;
    float f1, f2;
    char *s1, *s2;
    int comp;
    switch (heap->type) {
        case INT:
            i1 = ((int *)heap->items)[a];
            i2 = ((int *)heap->items)[b];
            if (i1 > i2)
                return 1;
            if (i1 < i2)
                return -1;
            return 0;
        case FLOAT:
            f1 = ((float *)heap->items)[a];
            f2 = ((float *)heap->items)[b];
            if (f1 > f2)
                return 1;
            if (f1 < f2)
                return -1;
            return 0;
        case STRING:
            s1 = ((char **)heap->items)[a];
            s2 = ((char **)heap->items)[b];
            comp = strcmp(s1, s2);
            if (comp > 0)
                return 1;
            if (comp < 0)
                return -1;
            return 0;
        default:
            fprintf(stderr, "error: unsupported heap item type\n");
            exit(1);
    }
}


/* delete a heap */
void heap_delete(Heap *heap) {
    if (heap->type == STRING) {
        for (int i = 0; i < heap->count; i++)
            free(((char **)heap->items)[i]);
    }
    free(heap->items);
    free(heap);
}


/* delete item at the specified index
 * should usually be used to delete the last element, otherwise this will
 * break the heap */
void heap_delete_item(Heap *heap, int index) {
    switch (heap->type) {
        case INT:
            ((int *)heap->items)[index] = 0;
            break;
        case FLOAT:
            ((float *)heap->items)[index] = 0;
            break;
        case STRING:
            free(((char **)heap->items)[index]);
            break;
    }
    heap->count--;

    /* eventually resize the heap */
    if (heap->count <= heap->size / 4)
        heap_resize_down(heap);
}


/* create a heap from an array
 * in a binary heap half of the items are parents and half of the items are
 * children, so we start from the middle and iterate backwards to sift down
 * items to their appropriate position */
Heap *heap_from_array(void *array, char type, int size) {
    Heap *heap;
    int i;
    switch (type) {
        case INT:
            heap = heap_init_sized(size, INT);
            for (i = 0; i < size; i++)
                ((int *)heap->items)[i] = ((int *)array)[i];
            break;
        case FLOAT:
            heap = heap_init_sized(size, FLOAT);
            for (i = 0; i < size; i++)
                ((float *)heap->items)[i] = ((float *)array)[i];
            break;
        case STRING:
            heap = heap_init_sized(size, STRING);
            for (i = 0; i < size; i++)
                ((char **)heap->items)[i] = ((char **)array)[i];
            break;
        default:
            fprintf(stderr, "error: unsupported item type\n");
            exit(1);
    }
    for (int i = (size - 2) / 2; i >= 0; i--) {
        heap_sift_down(heap, i, size - 1);
    }
    heap->count = size;
    return heap;
}


/* wrapper around the initializing function */
/* returns an empty heap with the base size */
Heap *heap_init(char type) {
    return heap_init_sized(BASE_SIZE, type);
}


/* initialize a heap storing items of the specifid type */
Heap *heap_init_sized(int size, char type) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    if (heap == NULL) {
        fprintf(stderr, "error: can't allocate memory to initialize heap\n");
        exit(1);
    }
    switch (type) {
        case INT:
            heap->items = calloc((size_t)size, sizeof(int));
            break;
        case FLOAT:
            heap->items = calloc((size_t)size, sizeof(float));
            break;
        case STRING:
            heap->items = calloc((size_t)size, sizeof(char *));
            break;
        default:
            fprintf(stderr, "error: heap item type not supported\n");
            exit(1);
    }
    if (heap->items == NULL) {
        fprintf(stderr, "error: can't allocate memory to initialize heap\n");
        exit(1);
    }
    heap->size = size;
    heap->type = type;
    heap->count = 0;
    return heap;
}


/* get index of parent from child index */
int heap_parent_index(int child_index) {
    return (child_index - 1) / 2;
}


/* pop item with highest value from heap, and maintain heap condition */
void *heap_pop(Heap *heap) {
    /* swap highest value item with last item */
    int last = heap->count-1;
    heap_swap_items(heap, 0, last);

    /* sift down item at index 0 to appropriate index */
    /* remember 'last' is the popped item index*/
    heap_sift_down(heap, 0, last-1);

    /* copy popped item and return pointer to it */
    void *result;
    char *to_pop;
    switch (heap->type) {
        case INT:
            result = malloc(sizeof(int));
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for heap item\n");
                exit(1);
            }
            *(int *)result = ((int *)heap->items)[last];
            break;
        case FLOAT:
            result = malloc(sizeof(float));
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for heap item\n");
                exit(1);
            }
            *(float *)result = ((float *)heap->items)[last];
            break;
        case STRING:
            to_pop = ((char **)heap->items)[last];
            result = malloc(strlen(to_pop)+1);
            if (result == NULL) {
                fprintf(stderr, "error: can't allocate memory for heap item\n");
                exit(1);
            }
            strcpy((char *)result, to_pop);
            break;
        default:
            fprintf(stderr, "error: unsupported heap item type\n");
            exit(1);
    }
    heap_delete_item(heap, last);
    return result;
}


/* get index of left child from parent index */
int heap_left_child_index(int parent_index) {
    return 2 * parent_index + 1;
}


/* resize heap when it's growing too large or shrinking too small */
void heap_resize(Heap *heap, int new_size) {
    if (new_size < BASE_SIZE)
        return;

    /* should probably check return value of realloc before assigning it
     * to heap->items, if realloc returns NULL I can't free heap->items */
    switch (heap->type) {
        case INT:
            heap->items = realloc(heap->items, sizeof(int) * (size_t)new_size);
            break;
        case FLOAT:
            heap->items = realloc(heap->items, sizeof(float) * (size_t)new_size);
            break;
        case STRING:
            heap->items = realloc(heap->items, sizeof(char *) * (size_t)new_size);
            break;
        default:
            fprintf(stderr, "error: heap item type not supported\n");
            exit(1);
    }
    if (heap->items == NULL) {
        fprintf(stderr, "error: can't allocate memory for heap items\n");
        exit(1);
    }

    heap->size = new_size;
}


/* decrease the size of the heap */
void heap_resize_down(Heap *heap) {
    heap_resize(heap, heap->size / 2);
}

/* increase the size of the heap */
void heap_resize_up(Heap *heap) {
    heap_resize(heap, heap->size * 2);
}


/* get index of right child from parent index */
int heap_right_child_index(int parent_index) {
    return 2 * parent_index + 2;
}


/* sift item down as far as necessary to maintain heap condition
 * start is the index of the element we want to sift down
 * elements between start and end indices (inclusive) respect the heap condition */
void heap_sift_down(Heap *heap, int start, int end) {
    while (1) {
        int left = heap_left_child_index(start);
        if (left > end) {
            left = -1;
        }
        int right = heap_right_child_index(start);
        if (right > end) {
            right = -1;
        }

        /* parent has both children */
        if (left != -1 && right != -1) {
            /* if left > right */
            if (heap_compare_items(heap, left, right) == 1) {
                /* if parent < left child, then swap them */
                if (heap_compare_items(heap, start, left) == -1) {
                    heap_swap_items(heap, start, left);
                    start = left;
                }
                /* else the heap condition is maintained and we stop */
                else {
                    break;
                }
            }

            /* if right > left */
            else {
                /* if parent < right child, then swap them */
                if (heap_compare_items(heap, start, right) == -1) {
                    heap_swap_items(heap, start, right);
                    start = right;
                }
                /* else the heap condition is maintained and we stop */
                else {
                    break;
                }
            }
        }

        /* parent has only left child and parent < left child */
        else if (left != -1 && heap_compare_items(heap, start, left) == -1) {
            heap_swap_items(heap, start, left);
            start = left;
        }

        else {
            break;
        }
    }
}


/* sift node up as far as necessary to ensure the path to the root of the heap
 * satisfies the heap condition */
void heap_sift_up(Heap *heap, int index) {
    while (heap_compare_items(heap, index, heap_parent_index(index)) == 1) {
        if (index == 0)
            break;
        heap_swap_items(heap, index, heap_parent_index(index));
        index = heap_parent_index(index);
    }
}


/* sort an array by converting to a heap */
void heap_sort(void *array, char type, int size) {
    Heap *heap = heap_from_array(array, type, size);
    /* sort items in ascending order */
    for (int last = size - 1; last > 0; last--) {
        heap_swap_items(heap, 0, last);
        heap_sift_down(heap, 0, last-1);
    }
    /* re-order items in original array */
    int i;
    switch (type) {
        case INT:
            for (i = 0; i < size; i++)
                ((int *)array)[i] = ((int *)heap->items)[i];
            break;
        case FLOAT:
            for (i = 0; i < size; i++)
                ((float *)array)[i] = ((float *)heap->items)[i];
            break;
        case STRING:
            for (i = 0; i < size; i++)
                ((char **)array)[i] = ((char **)heap->items)[i];
            break;
        default:
            fprintf(stderr, "error: unsupported item type\n");
            exit(1);
    }
}


/* swap two heap items based on their indices i and j */
void heap_swap_items(Heap *heap, int i, int j) {
    int int_tmp;
    float float_tmp;
    char *char_tmp;
    switch (heap->type) {
        case INT:
            int_tmp = ((int *)heap->items)[i];
            ((int *)heap->items)[i] = ((int *)heap->items)[j];
            ((int *)heap->items)[j] = int_tmp;
            break;
        case FLOAT:
            float_tmp = ((float *)heap->items)[i];
            ((float *)heap->items)[i] = ((float *)heap->items)[j];
            ((float *)heap->items)[j] = float_tmp;
            break;
        case STRING:
            char_tmp = ((char **)heap->items)[i];
            ((char **)heap->items)[i] = ((char **)heap->items)[j];
            ((char **)heap->items)[j] = char_tmp;
            break;
        default:
            fprintf(stderr, "error: unsupported heap item type\n");
            exit(1);
    }
}
