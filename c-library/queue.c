/* this queue library is implemented using two stacks, one stack for input
 * elements and another stack for output elements */

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


/* fill the queue "outstack" with elements from the "instack" */
void _fill_outstack(Queue *queue) {
    char t;
    while (!stack_isempty(queue->instack)) {
        t = stack_toptype(queue->instack);
        stack_push(queue->outstack, stack_pop(queue->instack), t);
    }
}


/* initialize an empty queue */
Queue *queue_init() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->length = 0;
    queue->instack = (Stack *) malloc(sizeof(Stack));
    queue->outstack = (Stack *) malloc(sizeof(Stack));
    return queue;
}


/* returns 1 if the queue is empty else 0 */
char queue_isempty(Queue *queue) {
    if (queue->length > 0)
        return FALSE;
    return TRUE;
}


/* returns a void pointer to the item next to be popped
 * you should check the item type first, so you can cast the value */
void *queue_pop(Queue *queue) {
    if (queue->outstack == NULL)
        queue->outstack = (Stack *) malloc(sizeof(Stack));
    if (stack_isempty(queue->outstack))
        _fill_outstack(queue);
    queue->length--;
    return stack_pop(queue->outstack);
}


/* push an item in the queue by passing a void pointer to it and the value type */
void queue_push(Queue *queue, void *item, char type) {
    if (queue->instack == NULL)
        queue->instack = (Stack *) malloc(sizeof(Stack));
    stack_push(queue->instack, item, type);
    queue->length++;
}


/* get the type of the item next to be popped */
char queue_typepeek(Queue *queue) {
    if (queue->outstack == NULL)
        queue->outstack = (Stack *) malloc(sizeof(Stack));
    if (stack_isempty(queue->outstack))
        _fill_outstack(queue);
    return stack_toptype(queue->outstack);
}


/* get the value of the item next to be popped */
void *queue_valpeek(Queue *queue) {
    if (queue->outstack == NULL)
        queue->outstack = (Stack *) malloc(sizeof(Stack));
    if (stack_isempty(queue->outstack))
        _fill_outstack(queue);
    return stack_topval(queue->outstack);
}
