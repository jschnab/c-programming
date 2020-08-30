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
