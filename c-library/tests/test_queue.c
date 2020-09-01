#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue.h"


int n_fail = 0;


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


int main(int argc, char *argv[]) {
    printf("Running tests on queues functions...\n\n");
    test_queue_init_1();
    test_queue_isempty_1();
    test_queue_isempty_2();
    test_queue_pop_1();
    test_queue_pop_2();
    printf("\nTests finished\n");
    printf("Number of failures: %d\n", n_fail);
    return 0;

}
