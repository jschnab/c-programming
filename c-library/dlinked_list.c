#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


enum DLIST_TYPES {
    INT    = 1,
    FLOAT  = 2,
    STRING = 3,
};


typedef struct dlnode {
    void *val;
    char type;
    struct dlnode *next;
    struct dlnode *prev;
} DListNode;


typedef struct dlist {
    DListNode *head;
    DListNode *tail;
    int n;
} DList;


DList *dlist_init();
void dlist_append(DList *, void *, char);


/* initialize an empty doubly-linked list */
DList *dlist_init() {
    DList *list = (DList *) malloc(sizeof(DList));
    if (list == NULL) {
        printf("error: memory not allocated to initialize list\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->n = 0;
    return list;
}


/* append a node at the end of the linked list */
/* if the list is empty, set the new node as head and tail */
void dlist_append(DList *list, void *val, char type) {
    DListNode *new = (DListNode *) malloc(sizeof(DListNode));
    if (new == NULL) {
        printf("error: malloc failed when appending node to list\n");
        exit(1);
    }

    switch (type) {
        case INT:
            new->val = (int *) malloc(sizeof(int));
            if (new == NULL) {
                printf("error: malloc failed when appending node to list\n");
                exit(1);
            }
            memcpy(new->val, val, sizeof(int));
            break;
        case FLOAT:
            new->val = (float *) malloc(sizeof(float));
            if (new == NULL) {
                printf("error: malloc failed when appending node to list\n");
                exit(1);
            }
            memcpy(new->val, val, sizeof(int));
            break;
        case STRING:
            new->val = (char *) malloc(strlen(val));
            if (new == NULL) {
                printf("error: malloc failed when appending node to list\n");
                exit(1);
            }
            memcpy(new->val, val, strlen(val));
            break;
    }
    new->type = type;

    /* if the list is empty */
    if (list->tail == NULL) {
        new->prev = new->next = NULL;
        list->head = list->tail = new;
        list->n = 1;
        return;
    }

    new->next = NULL;
    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;
    list->n++;
}
