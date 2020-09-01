#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


typedef struct queue {
    int length;
    Stack *instack;
    Stack *outstack;
} Queue;


void _fill_outstack(Queue *);
Queue *queue_init();
char queue_isempty(Queue *);
void *queue_pop(Queue *);
void queue_push(Queue *, void *, char);
char queue_typepeek(Queue *);
void *queue_valpeek(Queue *);
