#include <stdbool.h>
#include <stdio.h>


typedef struct heap {
    int *items;
    int length;
} Heap;


int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

int parent(int i) {
    return i / 2;
}

void max_heapify(Heap *h, int i) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int max;
        int tmp;
        if (l < h->length && h->items[i] < h->items[l]) {
            max = l;
        }
        else {
            max = i;
        }
        if (r < h->length && h->items[max] < h->items[r]) {
            max = r;
        }
        if (max == i) {
            return;
        }
        tmp = h->items[i];
        h->items[i] = h->items[max];
        h->items[max] = tmp;
        i = max;
    } 
}

void build_max_heap(Heap *h) {
    for (int i = h->length / 2; i >= 0; i--) {
        max_heapify(h, i);
    }
}

void heap_sort(Heap *h) {
    build_max_heap(h);
    int tmp;
    for (int i = h->length - 1; i > 0; i--) {
        tmp = h->items[i];
        h->items[i] = h->items[0];
        h->items[0] = tmp;
        h->length--;
        max_heapify(h, 0);
    }
}

int extract_max(Heap *h) {
    int max = h->items[0];
    h->items[0] = h->items[h->length-1];
    h->length--;
    max_heapify(h, 0);
    return max;
}

void increase_key(Heap *h, int i, int key) {
    if (key < h->items[i]) {
        printf("error: new key is smaller than current\n");
        return;
    }
    h->items[i] = key;
    int tmp;
    while (i > 0 && h->items[parent(i)] < h->items[i]) {
        tmp = h->items[i];
        h->items[i] = h->items[parent(i)];
        h->items[parent(i)] = tmp;
        i = parent(i);
    }
}

void max_heap_insert(Heap *h, int key) {
    h->items[h->length] = -1;
    increase_key(h, h->length, key);
    h->length++;
}

int main(int argc, char *argv[]) {
    Heap h = {NULL, 0};
    int items[] = {54, 32, 87, 65, 10, -1, -1, -1};
    h.items = items;
    h.length = 5;
    build_max_heap(&h);
    for (int i = 0; i < h.length; i++) {
        printf("items[%d] = %d\n", i, h.items[i]);
    }
    printf("\n");
    increase_key(&h, 4, 100);
    for (int i = 0; i < h.length; i++) {
        printf("items[%d] = %d\n", i, h.items[i]);
    }
    printf("\n");
    max_heap_insert(&h, 70);
    for (int i = 0; i < h.length; i++) {
        printf("items[%d] = %d\n", i, h.items[i]);
    }
    printf("\n");
    heap_sort(&h);
    for (int i = 0; i < 6; i++) {
        printf("%d ", h.items[i]);
    }
    printf("\n");
    return 0;
}
