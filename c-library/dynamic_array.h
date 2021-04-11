#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H


typedef struct darray {
    void *items;
    char type;
    int size;
    int count;
} DArray;


void darray_append(DArray *, void *);
int darray_compare_items(DArray *, int, int);
void darray_delete(DArray *);
void darray_delete_item(DArray *, int);
DArray *darray_init(char);
DArray *darray_init_sized(char, int);
void *darray_pop(DArray *);
void darray_quicksort(DArray *, int, int);
void darray_resize(DArray *, int);
void darray_resize_up(DArray *);
void darray_resize_down(DArray *);
void darray_sort(DArray *);
void darray_swap_items(DArray *, int, int);


#endif
