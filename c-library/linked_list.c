#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum LIST_TYPES {
    INT    = 1,
    FLOAT  = 2,
    STRING = 3,
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
void list_insert(ListNode *, void *, size_t, char, int);
void list_insert_front(ListNode **, void *, size_t, char);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
void list_to_array(ListNode *, void *, char type);
void list_to_strarray(ListNode *head, char *array[]);


/* append a node storing x at the end of the list */
void list_append(ListNode *head, void *val, size_t size, char type) {
    if (head == NULL)
        return;

    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL)
        return;
    new->val = malloc(size);
    new->type = type;
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
        new->type = head->type;
        ListNode *current = new;
        while (head->next != NULL) {
            current->next = (ListNode *) malloc(sizeof(ListNode));
            head = head->next;
            current = current->next;
            current->val = head->val;
            current->type = head->type;
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
    if (head != NULL) {
        previous->next = head->next;
        free(head);
    }
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
                return 0;
        }
        a = a->next;
        b = b->next;
    }
    return 1;
}


/* insert a value at a specific index where index > 0
 * if n > length list, value is inserted at the end */
void list_insert(ListNode *head, void *val, size_t size, char type, int n) {
    if (head != NULL && n > 0) {
        ListNode *previous;
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        new->val = malloc(size);
        memcpy(new->val, val, size);
        new->type = type;

        while (n-- > 0 && head != NULL) {
            previous = head;
            head = head->next;
        }
        previous->next = new;
        new->next = head;
    }
}


/* insert a value at the front of the list (index 0) */
void list_insert_front(ListNode **head, void *val, size_t size, char type) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    new->val = malloc(size);
    memcpy(new->val, val, size);
    new->type = type;
    new->next = *head;
    *head = new;
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


/* reverse a list */
void list_reverse(ListNode **head) {
    ListNode *reverse = NULL;
    ListNode *next;
    ListNode *current = *head;
    while (current != NULL) {
        next = current->next;
        current->next = reverse;
        reverse = current;
        current = next;
    }
    *head = reverse;
}


/* convert a list to an array */
void list_to_array(ListNode *head, void *array, char type) {
    while (head) {
        switch (type) {
            case FLOAT:
                *(float *)array = *(float *)head->val;
                array += sizeof(float);
                break;
            case INT:
                *(int *)array = *(int *)head->val;
                array += sizeof(int);
                break;
            default:
                printf("List node type not supported\n");
        }
        head = head->next;
    }
}


/* convert a list into an array of strings */
void list_to_strarray(ListNode *head, char *array[]) {
    for (int i = 0; head != NULL; i++) {
        array[i] = malloc(strlen((char *)head->val));
        memcpy(array[i], head->val, strlen((char *)head->val));
        head = head->next;
    }
}
