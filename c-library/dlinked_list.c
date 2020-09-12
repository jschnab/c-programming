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


void dlist_append(DListNode *, void *, char);


/* append a node at the end of the linked list */
/* if the list is empty (head is NULL), do nothing */
void dlist_append(DListNode *head, void *val, char type) {
    if (head == NULL)
        return;

    DListNode *current = head;
    while (head->next != NULL)
        head = head->next;

    DListNode *new = (DListNode *) malloc(sizeof(DListNode));
    if (new == NULL)
        return;

    switch (type) {
        case INT:
            new->val = (int *) malloc(sizeof(int));
            memcpy(new->val, val, sizeof(int));
            break;
        case FLOAT:
            new->val = (float *) malloc(sizeof(float));
            memcpy(new->val, val, sizeof(int));
            break;
        case STRING:
            new->val = (char *) malloc(strlen(val));
            memcpy(new->val, val, strlen(val));
            break;
    }

    new->type = type;
    new->next = NULL;
    new->prev = current;
    current->next = new;
}
