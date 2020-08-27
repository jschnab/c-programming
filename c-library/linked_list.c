#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum LIST_TYPES {
    INT    = 0,
    FLOAT  = 1,
    STRING = 2,
};


typedef struct lnode {
    void *val;
    struct lnode *next;  /* remember memory for this is not allocated */
    char type;
} ListNode;


void list_append(ListNode *, void *, size_t, char);
ListNode *list_copy(ListNode *);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
/*
void list_insert(ListNode *, int, int);
void list_insert_front(ListNode **, int);
*/
int list_length(ListNode *);
void list_print(ListNode *);
/*
void list_reverse(ListNode **);
void list_to_array(ListNode *, int *);
*/


/* append a node storing x at the end of the list */
void list_append(ListNode *head, void *val, size_t size, char type) {
    if (head == NULL)
        return;

    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL)
        return;
    new->val = malloc(size);
    memcpy(new->val, val, size);
    ListNode *current;
    current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
}


/* copies a list */
ListNode *list_copy(ListNode *head) {
    if (head != NULL) {
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        new->val = head->val;
        ListNode *current = new;
        while (head->next != NULL) {
            current->next = (ListNode *) malloc(sizeof(ListNode));
            head = head->next;
            current = current->next;
            current->val = head->val;
        }
        return new;
    }
    return NULL;
}


/* delete the nth element of a list
 * if n > length of list, do nothing */
void list_delete(ListNode *head, int n) {
    if (n == 0) {
        *head = *(head->next); 
        return;
    } 
    ListNode *previous;
    while (n-- > 0 && head != NULL) {
        previous = head;
        head = head->next;
    }
    if (head != NULL)
        previous->next = head->next;
}


/* determines if two list are identical */
char list_equal(ListNode *a, ListNode *b) {
    if (list_length(a) != list_length(b))
        return 0;
    while (a != NULL) {
        if (a->type != b->type)
            return 0;
        switch(a->type) {
            case INT:
                if (*(int *)a->val != *(int *)b->val)
                    return 0;
                break;
            case FLOAT:
                if (*(float *)a->val != *(float *)b->val)
                    return 0;
                break;
            case STRING:
                return strcmp((char *)a->val, (char *)b->val);
                break;
            default:
                printf("List node type not supported\n");
                return 1;
        }
        a = a->next;
        b = b->next;
    }
    return 1;
}


/* return the number of nodes in the list */
int list_length(ListNode *head) {
    if (head == NULL)
        return 0;
    int n = 0;
    while (head != NULL) {
        n++;
        head = head->next;
    }
    return n;
}


/* print values stored in the list */
void list_print(ListNode *head) {
    while (head != NULL) {
        switch(head->type) {
            case INT:
                printf((head->next != NULL) ? "%d -> " : "%d\n", *(int *)head->val);
                break;
            case FLOAT:
                printf((head->next != NULL) ? "%.3f -> " : "%.3f\n", *(float *)head->val);
                break;
            case STRING:
                printf((head->next != NULL) ? "%s -> " : "%s\n", (char *)head->val);
                break;
            default:
                printf((head->next != NULL) ? "? -> " : "?\n");
        }
        head = head->next;
    }
}
