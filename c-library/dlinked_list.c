#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "data_types.h"


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
int dlist_compare_nodes(DListNode *, DListNode *);
DList *dlist_copy(DList *);
DListNode *dlist_copy_node(DListNode *);
DListNode *dlist_create_node(void *, char);
void dlist_delete(DList *, int);
char dlist_equal(DList *, DList *);
DList *dlist_from_array(void *, char, int);
DListNode *dlist_get_node(DList *, int);
char dlist_get_type(DList *, int);
void *dlist_get_value(DList *, int);
DList *dlist_init();
void dlist_insert(DList **, void *, char, int);
int dlist_length(DList *);
void dlist_print(DList *);
DList *dlist_slice(DList *, int, int);
void dlist_sort(DList *);
void dlist_sort_helper(DList *, int, int);
void dlist_swap_nodes(DListNode *, DListNode *);
void dlist_to_array(DList *, void *, char);
void dlist_to_strarray(DList *, char *array[]);


/* append a node at the end of the linked list */
/* if the list is empty, set the new node as head and tail */
void dlist_append(DList *list, void *val, char type) {
    DListNode *new = dlist_create_node(val, type);

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


/* compare the value of two nodes, the return value is an integer:
 *  0 if nodes have the same value
 * -1 if node A is < node B and nodes have a numerical value
 *  1 if node A is > node B and nodes have a numerical value
 *  result of strcmp() if nodes have a string value
 *
 *  Note: this function assumes nodes have the same type */
int dlist_compare_nodes(DListNode *a, DListNode *b) {
    int i1, i2;
    float f1, f2;
    char *s1, *s2;
    switch (a->type) {
        case INT:
            i1 = *(int *)a->val;
            i2 = *(int *)b->val;
            if (i1 < i2)
                return -1;
            else if (i1 > i2)
                return 1;
            return 0;
        case FLOAT:
            f1 = *(float *)a->val;
            f2 = *(float *)b->val;
            if (f1 < f2)
                return -1;
            else if (f1 > f2)
                return 1;
            return 0;
        case STRING:
            s1 = (char *)a->val;
            s2 = (char *)b->val;
            return strcmp(s1, s2);
        default:
            printf("error: node type not recognized\n");
            exit(1);
    }
}


/* copy a list */
DList *dlist_copy(DList *list) {
    if (list == NULL)
        return NULL;
    DList *new = dlist_init();
    DListNode *current = list->head;
    while (current != NULL) {
        dlist_append(new, current->val, current->type);
        current = current->next;
    }
    return new;
}


/* copy the value and type of a doubly-linked node
 * this does not copy the 'next' and 'prev' pointers */
DListNode *dlist_copy_node(DListNode *node) {
    DListNode *new = dlist_create_node(node->val, node->type);
    return new;
}


/* return a node with the value stored in a void pointer */
DListNode *dlist_create_node(void *value, char type) {
    DListNode *new = (DListNode *) malloc(sizeof(DListNode));
    if (new == NULL) {
        printf("error: malloc failed when creating node\n");
        exit(1);
    }

    switch (type) {
        case INT:
            new->val = (int *) malloc(sizeof(int));
            if (new->val == NULL) {
                printf("error: malloc failed when creating node\n");
                exit(1);
            }
            memcpy(new->val, value, sizeof(int));
            break;
        case FLOAT:
            new->val = (float *) malloc(sizeof(float));
            if (new->val == NULL) {
                printf("error: malloc failed when creating node\n");
                exit(1);
            }
            memcpy(new->val, value, sizeof(float));
            break;
        case STRING:
            new->val = (char *) malloc(strlen(value));
            if (new->val == NULL) {
                printf("error: malloc failed when creating node\n");
                exit(1);
            }
            memcpy(new->val, value, strlen(value));
            break;
    }
    new->type = type;
    new->next = NULL;
    new->prev = NULL;

    return new;
}


/* delete nth node of list
 * raise an error if trying to delete node past the last node */
void dlist_delete(DList *list, int n) {
    if (n >= list->n) {
        printf("error: trying to delete past last node\n");
        exit(1);
    }

    /* position 'current' pointer on the node to delete */
    DListNode *current = list->head;
    while (n-- > 0)
        current = current->next;

    if (current->prev != NULL)
        current->prev->next = current->next;
    /* if we delete the first node, update 'head' pointer */
    else
        list->head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;
    /* if we delete the last node, update 'tail' pointer */
    else
        list->tail = current->prev;

    free(current);
    list->n--;
}


/* determine if two lists are equal */
char dlist_equal(DList *a, DList *b) {
    if (dlist_length(a) != dlist_length(b))
        return 0;

    DListNode *cur_a = a->head;
    DListNode *cur_b = b->head;

    /* traverse list from head to tail */
    while (cur_a != NULL) {
        if (cur_a->type != cur_b->type)
            return 0;

        switch (cur_a->type) {
            case INT:
                if (*(int *)cur_a->val != *(int *)cur_b->val)
                    return 0;
            case FLOAT:
                if (*(float *)cur_a->val != *(float *)cur_b->val)
                    return 0;
            case STRING:
                if (strcmp((char *)cur_a->val, (char *)cur_b->val) != 0)
                    return 0;
        }
        cur_a = cur_a->next;
        cur_b = cur_b->next;
    }

    /* check tail pointers are correct */
    if (dlist_length(a) > 0 && a->tail->type != b->tail->type)
        return 0;

    return 1;
}


/* build list from an array */
DList *dlist_from_array(void *array, char type, int length) {
    DList *list = dlist_init();
    for (int i = 0; i < length; i++)
        switch (type) {
            case INT:
                dlist_append(list, &((int *)array)[i], INT);
                break;
            case FLOAT:
                dlist_append(list, &((float *)array)[i], FLOAT);
                break;
            case STRING:
                dlist_append(list, ((char **)array)[i], STRING);
                break;
            default:
                printf("error: data type not supported\n");
                exit(1);
        }
    return list;
}


/* return a pointer to the nth node of the list */
DListNode *dlist_get_node(DList *list, int n) {
    DListNode *current;
    /* decide if we reach node from head or tail */
    if (n < dlist_length(list) - 1 - n) {
        current = list->head;
        while (n-- > 0)
            current = current->next;
        return current;
    }
    else {
        current = list->tail;
        while (n++ < dlist_length(list) - 1)
            current = current->prev;
        return current;
    }
}


/* get the type of the nth node */
char dlist_get_type(DList *list, int n) {
    DListNode *current = list->head;
    if (n > list->n - 1) {
        printf("error: index %d is out of bounds\n", n);
        exit(1);
    }
    while (n-- > 0)
        current = current->next;
    return current->type;
}


/* get the value of the nth node
 * this returns a void pointer, you should call dlist_get_type()
 * to know which type to cast this into, if needed */
void *dlist_get_value(DList *list, int n) {
    DListNode *current = list->head;
    if (n > list->n - 1) {
        printf("error: index %d is out of bounds\n", n);
        exit(1);
    }
    while (n-- > 0)
        current = current->next;
    return current->val;
}


/* initialize an empty doubly-linked list */
DList *dlist_init() {
    DList *list = (DList *) malloc(sizeof(DList));
    if (list == NULL) {
        printf("error: malloc when initializing list\n");
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
    DListNode *new = dlist_create_node(value, type);

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
    printf("[ ");
    while (current != NULL) {
        switch (current->type) {
            case INT:
                printf((current->next != NULL) ? "%d <-> " : "%d", *(int *)current->val);
                break;
            case FLOAT:
                printf((current->next != NULL) ? "%.3f <-> " : "%.3f", *(float *)current->val);
                break;
            case STRING:
                printf((current->next != NULL) ? "%s <-> " : "%s", (char *)current->val);
                break;
            default:
                printf((current->next != NULL) ? "? <-> " : "?");
        }
        current = current->next;
    }
    printf(" ]\n");
}


/* slice a list based on start (inclusive) and end (exclusive) integers
 * this returns a deep copy of the list */
DList *dlist_slice(DList *list, int start, int end) {
    if (start > end) {
        printf("error: need start < end when slicing list\n");
        exit(1);
    }

    DList *new = dlist_copy(list);
    /* remove heading nodes */
    while (start-- > 0)
        dlist_delete(new, 0);

    /* remove trailing nodes */
    while (end++ < list->n)
        dlist_delete(new, new->n-1);

    return new;
}


/* sort a list in place with quicksort, recursively
 * assumes all nodes have the same type */
void dlist_sort(DList *list) {
    dlist_sort_helper(list, 0, dlist_length(list) - 1);
}


/* helper function for dlist_sort() */
void dlist_sort_helper(DList *list, int left, int right) {
    if (left >= right)
        return;

    int pivot = left;
    DListNode *current_node = dlist_get_node(list, left);
    DListNode *pivot_node = dlist_get_node(list, pivot);
    DListNode *right_node = dlist_get_node(list, right);

    for (int i = left; i < right; i++) {
        if (dlist_compare_nodes(current_node, right_node) <= 0) {
            dlist_swap_nodes(current_node, pivot_node);
            pivot_node = pivot_node->next;
            pivot++;
        }
        current_node = current_node->next;
    }

    dlist_swap_nodes(pivot_node, right_node);
    dlist_sort_helper(list, left, pivot - 1);
    dlist_sort_helper(list, pivot + 1, right);
}


/* swap two nodes of the list */
void dlist_swap_nodes(DListNode *a, DListNode *b) {
    if (a == b)
        return;
    void *tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}


/* copy the values of the list into the provided array
 * the array length must be greater than or equal to the list length */
void dlist_to_array(DList *list, void *array, char type) {
    DListNode *current = list->head;
    for (int i = 0; current != NULL; i++, current = current->next) {
        switch (type) {
            case INT:
                ((int *)array)[i] = *(int *)current->val;
                break;
            case FLOAT:
                ((int *)array)[i] = *(float *)current->val;
                break;
        }
    }
}


/* copy the strings stored in a list into the provided array
 * the array length must be greater than or equal to the list length */
void dlist_to_strarray(DList *list, char *array[]) {
    DListNode *current = list->head;
    for (int i = 0; current != NULL; i++, current = current->next) {
        array[i] = (char *) malloc(strlen((char *)current->val));
        memcpy(array[i], current->val, strlen((char *)current->val));
    }
}
