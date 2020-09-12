#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue.h"


int n_fail = 0;


/* test if freshly initialized queue is empty
 * and has empty pointers for its stacks */
void test_queue_init_1() {
    Queue *queue = queue_init();
    if (queue->length != 0 || queue->instack == NULL || queue->outstack == NULL) {
        printf("test_queue_init_1: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_init_1: PASS\n");
    free(queue);
}


/* test queue_isempty() returns TRUE for empty queue */
void test_queue_isempty_1() {
    Queue *queue = queue_init();
    if (!queue_isempty(queue)) {
        printf("test_queue_isempty_1: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_isempty_1: PASS\n");
    free(queue);
}


/* test queue_isempty() returns FALSE for queue with 1 element */
void test_queue_isempty_2() {
    Queue *queue = queue_init();
    int item = 1;
    queue_push(queue, &item, INT);
    if (queue_isempty(queue)) {
        printf("test_queue_isempty_2: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_isempty_2: PASS\n");
    free(queue);
}


/* check element value and that queue is empty after pop from queue 
 * with 1 element, this also tests that queue_push() works correctly */
void test_queue_pop_1() {
    Queue *queue = queue_init();
    int item = 1;
    queue_push(queue, &item, INT);
    if (*(int *)queue_pop(queue) != 1 || !queue_isempty(queue)) {
        printf("test_queue_pop_1: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_pop_1: PASS\n");
    free(queue);
}


/* check element value and length = 1 after pop from queue with 1 element
 * this also tests that queue_push() works correctly */
void test_queue_pop_2() {
    Queue *queue = queue_init();
    int values[] = {1, 2};
    queue_push(queue, &values[0], INT);
    queue_push(queue, &values[1], INT);
    int result = *(int *) queue_pop(queue);
    if (result != 1 || queue->length != 1) {
        printf("test_queue_pop_2: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_pop_2: PASS\n");
    free(queue);
}


/* test if queue_typepeek returns the correct type
 * and keeps the queue intact */
void test_queue_typepeek_1() {
    Queue *queue = queue_init();
    int i = 1;
    float f = 2.0;
    queue_push(queue, &i, INT);
    queue_push(queue, &f, FLOAT);
    if (queue_typepeek(queue) != INT || queue->length != 2) {
        printf("test_queue_typepeek_1: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_typepeek_1: PASS\n");
    free(queue);
}


/* test if queue_valpeek returns the correct numeric value
 * and keeps the queue intact */
void test_queue_valpeek_1() {
    Queue *queue = queue_init();
    int i = 1;
    float f = 2.0;
    char *s = "hello";
    queue_push(queue, &i, INT);
    queue_push(queue, &f, FLOAT);
    queue_push(queue, s, STRING);
    if (*(int *) queue_valpeek(queue) != 1 || queue->length != 3) {
        printf("test_queue_valpeek_1: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_valpeek_1: PASS\n");
    free(queue);
}


/* test if queue_valpeek returns the correct string value
 * and keeps the queue intact */
void test_queue_valpeek_2() {
    Queue *queue = queue_init();
    int i = 1;
    float f = 2.0;
    char *s = "hello";
    queue_push(queue, s, STRING);
    queue_push(queue, &i, INT);
    queue_push(queue, &f, FLOAT);
    if (strcmp(queue_valpeek(queue), s) != 0 || queue->length != 3) {
        printf("test_queue_valpeek_2: FAILED\n");
        n_fail++;
        free(queue);
        return;
    }
    printf("test_queue_valpeek_2: PASS\n");
    free(queue);
}


int main(int argc, char *argv[]) {
    printf("Running tests on queues functions...\n\n");
    test_queue_init_1();
    test_queue_isempty_1();
    test_queue_isempty_2();
    test_queue_pop_1();
    test_queue_pop_2();
    test_queue_typepeek_1();
    test_queue_valpeek_1();
    test_queue_valpeek_2();
    printf("\nTests finished\n");
    printf("Number of failures: %d\n", n_fail);
    return 0;
}
