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


char stack_isempty(Stack *);
void *stack_pop(Stack *);
void stack_push(Stack *, void *, char);
char stack_toptype(Stack *);
void *stack_topval(Stack *);
