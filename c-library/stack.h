#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "data_types.h"


typedef struct stack {
    int length;
    ListNode *items;
} Stack;


Stack *stack_init();
char stack_isempty(Stack *);
void *stack_pop(Stack *);
void stack_push(Stack *, void *, char);
char stack_toptype(Stack *);
void *stack_topval(Stack *);
