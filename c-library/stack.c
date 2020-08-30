/* this stack library is implemented using a singly linked list
 * the top item of the stack is the head of the list */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


enum BOOL {
    TRUE  = 1,
    FALSE = 0,
};


typedef struct stack {
    int length;
    ListNode *items;
} Stack;


char isempty(Stack *);
void *pop(Stack *);
void push(Stack *, void *, char);
char toptype(Stack *);
void *topval(Stack *);


/* returns 1 if the stack is empty else 0 */
char isempty(Stack *stack) {
    if (stack->length > 0)
        return FALSE;
    return TRUE;
}

/* returns a void pointer to the value item at the top of the stack
 * you should check the item type first, so you can cast the value */
void *pop(Stack *stack) {
    if (isempty(stack) == TRUE) {
        printf("error: can't pop empty stack\n");
        return NULL;
    }
    char type = toptype(stack);
    void *value;
    switch (type) {
        case INT:
            value = malloc(sizeof(int));
            memcpy(value, stack->items->val, sizeof(int));
            break;
        case FLOAT:
            value = malloc(sizeof(float));
            memcpy(value, stack->items->val, sizeof(float));
            break;
        case STRING:
            value = malloc(sizeof(strlen(stack->items->val)));
            memcpy(value, stack->items->val, sizeof(strlen(stack->items->val)));
            break;
        default:
            printf("error: type of stack element is not supported\n");
            return NULL;
    }

    /* if there is only one item, we directly delete it
     * because functions on list nodes do not handle this */
    if (stack->length == 1) {
        free(stack->items);
        stack->items = NULL;
    }
    else
        list_delete(stack->items, 0);
    stack->length--;
    return value;
}


/* push a value to the stack by passing a void pointer to it and the value type */
void push(Stack *stack, void *item, char type) {
    list_insert_front(&stack->items, item, type);
    stack->length++;
}


/* get the type of the item at the top of the stack */
char toptype(Stack *stack) {
    if (isempty(stack) == TRUE) {
        printf("error: stack is empty\n");
        return 0;
    }
    return stack->items->type;
}


/* get the value of the item at the top of the stack (without popping) */
void *topval(Stack *stack) {
    if (isempty(stack) == TRUE) {
        printf("error: stack is empty\n");
        return NULL;
    }
    return stack->items->val;
}
