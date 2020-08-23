#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef struct lnode {
    void *val;
    struct lnode *next;  /* remember memory for this is not allocated */
} ListNode;


void list_append(ListNode *, void *, size_t);
/*
ListNode *list_copy(ListNode *);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
void list_insert(ListNode *, int, int);
void list_insert_front(ListNode **, int);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
void list_to_array(ListNode *, int *);
*/


/* append a node storing x at the end of the list */
void list_append(ListNode *head, void *val, size_t size) {
    if (head == NULL)
        return;

    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL)
        return;
    new->val = malloc(size);
    for (int i = 0; i < size; i++)
        *(char *)(new->val + i) = *(char *)(val + i);

    ListNode *current;
    current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
}


