#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"


typedef struct lnode {
    void *val;
    struct lnode *next;  /* remember memory for this is not allocated */
    char type;
} ListNode;


void list_append(ListNode *, void *, char);
ListNode *list_copy(ListNode *);
ListNode *list_create(void *, char);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
void list_insert(ListNode *, void *, char, int);
void list_insert_front(ListNode **, void *, char);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
void list_to_array(ListNode *, void *, char);
void list_to_strarray(ListNode *head, char *array[]);


/* append a node storing x at the end of a non-null list */
void list_append(ListNode *head, void *val, char type) {
    if (head == NULL)
        return;

    ListNode *new = list_create(val, type);
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


/* create a new node given a pointer to a value and a type */
ListNode *list_create(void *val, char type) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL) {
        printf("error: malloc failed when creating new list node\n");
        exit(1);
    }

    switch (type) {
        case INT:
            new->val = malloc(sizeof(int));
            memcpy(new->val, val, sizeof(int));
            break;
        case FLOAT:
            new->val = malloc(sizeof(float));
            memcpy(new->val, val, sizeof(float));
            break;
        case STRING:
            new->val = malloc(strlen((char *)val));
            memcpy(new->val, val, strlen((char *)val));
            break;
    }
    new->type = type;
    return new;
}


/* delete the nth element of a list
 * if n > length of list or the node is the only one, do nothing */
void list_delete(ListNode *head, int n) {
    if (n == 0) {
        if (head->next != NULL) {
            ListNode *next = head->next;
            *head = *(head->next); 
            free(next);
        }
        else
            printf("error: can't delete the only node of the list\n");
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


/* determines if two list are identical, returns a char:
 * 0 if the lists are not equal
 * 1 if the lists are equal */
char list_equal(ListNode *a, ListNode *b) {
    if (list_length(a) != list_length(b)) {
        return 0;
    }
    while (a != NULL) {
        if (a->type != b->type) {
            return 0;
        }
        switch(a->type) {
            case INT:
                if (*(int *)a->val != *(int *)b->val) {
                    return 0;
                }
                break;
            case FLOAT:
                if (*(float *)a->val != *(float *)b->val)
                    return 0;
                break;
            case STRING:
                return strcmp((char *)a->val, (char *)b->val);
            default:
                printf("List node type not supported\n");
                return 0;
        }
        a = a->next;
        b = b->next;
    }
    return 1;
}


/* make a list from a variable number of arguments */
ListNode *list_from_args(int n, char type, ...) {
    if (n-- > 0) {
        int i;
        float f;
        char *s;
        va_list values;
        va_start(values, type);
        ListNode *head = (ListNode *) malloc(sizeof(ListNode));
        head->type = type;

        switch (type) {
            case INT:
                i = va_arg(values, int);
                head->val = malloc(sizeof(int));
                memcpy(head->val, &i, sizeof(int));;
                break;
            case FLOAT:
                f = (float) va_arg(values, double);
                head->val = malloc(sizeof(float));
                memcpy(head->val, &f, sizeof(float));
                break;
            case STRING:
                s = va_arg(values, char *);
                head->val = malloc(strlen(s));
                memcpy(head->val, s, strlen(s));
                break;
            default:
                printf("list node type not supported\n");
                return head;
        }

        ListNode *current = head;
        while (n-- > 0) {
            current->next = (ListNode *) malloc(sizeof(ListNode));
            current = current->next;
            current->type = type;

            switch (type) {
                case INT:
                    i = va_arg(values, int);
                    current->val = malloc(sizeof(int));
                    memcpy(current->val, &i, sizeof(int));;
                    break;
                case FLOAT:
                    f = (float) va_arg(values, double);
                    current->val = malloc(sizeof(float));
                    memcpy(current->val, &f, sizeof(float));
                    break;
                case STRING:
                    s = va_arg(values, char *);
                    current->val = malloc(strlen(s));
                    memcpy(current->val, s, strlen(s));
                    break;
                default:
                    printf("list node type not supported\n");
                    return head;
            }
        }
        va_end(values);
        return head;
    }
    return NULL;
}


/* insert a value at a specific index where index > 0
 * if n > length list, value is inserted at the end */
void list_insert(ListNode *head, void *val, char type, int n) {
    if (head != NULL && n > 0) {
        ListNode *previous;
        ListNode *new = list_create(val, type);
        while (n-- > 0 && head != NULL) {
            previous = head;
            head = head->next;
        }
        previous->next = new;
        new->next = head;
    }
}


/* insert a value at the front of the list (index 0) */
void list_insert_front(ListNode **head, void *val, char type) {
    ListNode *new = list_create(val, type);
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
