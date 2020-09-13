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


void dlist_append(DList *, void *, char);
DList *dlist_init();
void dlist_insert(DList **, void *, char, int);
int dlist_length(DList *);
void dlist_print(DList *);


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
            if (new->val == NULL) {
                printf("error: malloc failed when appending node to list\n");
                exit(1);
            }
            memcpy(new->val, val, sizeof(int));
            break;
        case FLOAT:
            new->val = (float *) malloc(sizeof(float));
            if (new->val == NULL) {
                printf("error: malloc failed when appending node to list\n");
                exit(1);
            }
            memcpy(new->val, val, sizeof(int));
            break;
        case STRING:
            new->val = (char *) malloc(strlen(val));
            if (new->val == NULL) {
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


/* insert a node in the list
 * provide the address of a pointer to a list,
 * a void pointer to the value to insert, its type,
 * and the position where to insert the node in the list
 * Note: if position > length of list, append node at the end */
void dlist_insert(DList **list, void *value, char type, int position) {
    DListNode *new = (DListNode *) malloc(sizeof(DListNode));
    if (new == NULL) {
        printf("error: malloc failed when insert node in list\n");
        exit(1);
    }
    new->type = type;
    new->next = NULL;
    new->prev = NULL;

    switch (type) {
        case INT:
            new->val = (int *) malloc(sizeof(int));
            if (new->val == NULL) {
                printf("error: malloc failed when inserting node to list\n");
                exit(1);
            }
            memcpy(new->val, value, sizeof(int));
            break;
        case FLOAT:
            new->val = (float *) malloc(sizeof(float));
            if (new->val == NULL) {
                printf("error: malloc failed when inserting node to list\n");
                exit(1);
            }
            memcpy(new->val, value, sizeof(int));
            break;
        case STRING:
            new->val = (char *) malloc(strlen(value));
            if (new->val == NULL) {
                printf("error: malloc failed when inserting node to list\n");
                exit(1);
            }
            memcpy(new->val, value, strlen(value));
            break;
    }

    /* we insert at the beginning of the list */
    if (position == 0) {
        new->next = (*list)->head;
        (*list)->head->prev = new;
        (*list)->head = new;
        (*list)->n++;
        return;
    }

    DListNode *current = (*list)->head;
    while (--position > 0 && current->next != NULL)
        current = current->next;

    if (current->next != NULL)
        current->next->prev = new;
    else
        /* we are inserting the node at the end
         * so we update the 'tail' pointer */
        (*list)->tail = new;

    new->next = current->next;
    new->prev = current;
    current->next = new;

    (*list)->n++;
}


/* get the length of the list */
int dlist_length(DList *list) {
    return list->n;
}


/* print the linked list */
void dlist_print(DList *list) {
    DListNode *current = list->head;
    while (current != NULL) {
        switch (current->type) {
            case INT:
                printf((current->next != NULL) ? "%d <-> " : "%d\n", *(int *)current->val);
                break;
            case FLOAT:
                printf((current->next != NULL) ? "%.3f <-> " : "%.3f\n", *(float *)current->val);
                break;
            case STRING:
                printf((current->next != NULL) ? "%s <-> " : "%s\n", (char *)current->val);
                break;
            default:
                printf((current->next != NULL) ? "? <-> " : "?\n");
        }
        current = current->next;
    }
}
