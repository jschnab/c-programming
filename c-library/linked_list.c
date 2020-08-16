#include <stdio.h>
#include <stdlib.h>


typedef struct lnode {
    int val;
    struct lnode *next;  /* remember memory for this is not allocated */
} ListNode;


void list_append(ListNode *, int);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
void list_insert(ListNode *, int, int);
void list_insert_front(ListNode **, int);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
ListNode *list_copy(ListNode *);
void list_to_array(ListNode *, int *);


int other_main(int argc, char *argv[]) {
    ListNode *head = (ListNode *) malloc(sizeof(ListNode));
    if (head != NULL) {
        head->val = 1;
    }
    list_append(head, 2);
    list_append(head, 3);
    printf("original list: ");
    list_print(head);
    printf("length = %d\n", list_length(head));
    printf("\n");

    printf("convert list to array\n");
    int array[3];
    list_to_array(head, array);
    for (int i = 0; i < 3; i++)
        printf("array[%d] = %d\n", i, array[i]);
    printf("\n");

    int n = 5;
    printf("deleting node at index %d: ", n);
    list_delete(head, n);
    list_print(head);
    printf("length = %d\n", list_length(head));
    printf("\n");

    n = 9;
    printf("inserting %d at the front\n", n);
    list_insert_front(&head, n);
    list_print(head);
    printf("length = %d\n", list_length(head));
    printf("\n");

    printf("reverse list: ");
    list_reverse(&head);
    list_print(head);
    printf("\n");

    n = 5;
    printf("inserting value 4 at index %d: ", n);
    list_insert(head, 4, n);
    list_print(head);
    printf("length = %d\n", list_length(head));
    printf("\n");

    printf("copy list: ");
    ListNode *copy = list_copy(head);
    list_print(copy);
    printf("length = %d\n", list_length(copy));
    printf("\n");

    ListNode *other = (ListNode *) malloc(sizeof(ListNode));
    other->val = 1;
    list_append(other, 3);
    list_append(other, 4);
    printf("comparing two lists:\n");
    printf("list 1: ");
    list_print(head);
    printf("list 2: ");
    list_print(other);
    printf("list 1 %s list 2\n", list_equal(head, other) ? "=" : "!=");
    printf("\n");

    ListNode *another = (ListNode *) malloc(sizeof(ListNode));
    another->val = 1;
    list_append(another, 3);
    list_append(another, 5);
    printf("comparing two lists:\n");
    printf("list 1: ");
    list_print(head);
    printf("list 2: ");
    list_print(another);
    printf("list 1 %s list 2\n", list_equal(head, another) ? "=" : "!=");

    return 0;
}


/* append a node storing x at the end of the list */
void list_append(ListNode *head, int x) {
    if (head == NULL)
        return;

    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL)
        return;
    new->val = x;

    ListNode *current;
    current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
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
        if (a->val != b->val)
            return 0;
        a = a->next;
        b = b->next;
    }
    return 1;
}


/* insert a value at a specific index where index > 0
 * if n > length list, value is inserted at the end */
void list_insert(ListNode *head, int val, int n) {
    if (head != NULL && n > 0) {
        ListNode *previous;
        ListNode *new = (ListNode *) malloc(sizeof(ListNode));
        new->val = val;

        while (n-- > 0 && head != NULL) {
            previous = head;
            head = head->next;
        }
        previous->next = new;;
        new->next = head;
    }
}


/* insert a value at the front of the list (index 0) */
void list_insert_front(ListNode **head, int val) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    new->val = val;
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
        printf((head->next != NULL) ? "%d -> " : "%d\n", head->val);
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


void list_to_array(ListNode *head, int *array) {
    while (head) {
        *array++ = head->val;
        head = head->next;
    }
}


/* SANDBOX 
 * the following functions should be considered in draft stage and are
 * here before being deprecated */

/* insert a value at a specific index */
ListNode *insert2(ListNode *head, int val, int n) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    new->val = val;

    if (head != NULL) {
        ListNode *first = (ListNode *) malloc(sizeof(ListNode));
        first->next = head;
        ListNode *current = first;
        while (n-- > 0) {
            current = current->next;
            if (current == NULL && n >= 0) {
                printf("index error during insertion: n > length\n");
                return first->next;
            }
        }
        new->next = current->next;
        current->next = new;
        return first->next;
    }

    return new;
}


/* delete the nth element of a list
 * if n > length of list, delete last element */
ListNode *delete2(ListNode *head, int n) {
    if (head != NULL) {
        ListNode *first = (ListNode *) malloc(sizeof(ListNode));
        first->next = head;
        ListNode *current = first;
        while (n-- > 0) {
            current = current->next;
            if (current->next == NULL) {
                printf("index error during deletion: n > length\n");
                return first->next;
            }
        }
        current->next = current->next->next;
        return first->next;
    }
    return NULL;
}


/* append a node storing x at the end of the list */
ListNode *list_append2(ListNode *head, int x) {
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if (new == NULL)
        return NULL;
    new->val = x;

    if (head == NULL)
        return new;

    ListNode *current;
    current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
    return head;
}

