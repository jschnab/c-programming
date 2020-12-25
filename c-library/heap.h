#ifndef HEAP_H
#define HEAP_H

typedef struct heap {
    void *items;
    char type;
    int size;
    int count;
} Heap;


void heap_add(Heap *, void *);
int heap_compare_items(Heap *, int, int);
void heap_delete(Heap *);
void heap_delete_item(Heap *, int);
Heap *heap_init(char);
Heap *heap_init_sized(int, char);
int heap_parent_index(int);
int heap_left_child_index(int);
int heap_right_child_index(int);
void heap_sift_up(Heap *, int);
void heap_swap_items(Heap *, int, int);


#endif  /* HEAP_H */
