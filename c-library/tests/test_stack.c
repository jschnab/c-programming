#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack.h"


static int n_fail = 0;


/* test empty stack */
void test_isempty_1() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (isempty(stack) == TRUE) {
        printf("test_isempty_1: PASS\n");
        return;
    }
    printf("test_isempty_1: FAILED\n");
    n_fail++;
}


/* test empty stack */
void test_isempty_2() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int value = 1;
    push(stack, &value, INT);
    if (isempty(stack) == FALSE) {
        printf("test_isempty_2: PASS\n");
        return;
    }
    printf("test_isempty_2: FAILED\n");
    n_fail++;
}


/* pop one integer item from stack */
void test_pop_1() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int values[] = {1, 2};
    push(stack, &values[0], INT);
    push(stack, &values[1], INT);
    if (*(int *) pop(stack) != 2) {
        printf("test_pop_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_pop_1: PASS\n");
}


/* pop two integer item from stack */
void test_pop_2() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int values[] = {1, 2};
    push(stack, &values[0], INT);
    push(stack, &values[1], INT);
    if (*(int *) pop(stack) != 2) {
        printf("test_pop_2: FAILED\n");
        n_fail++;
        return;
    }
    if (*(int *) pop(stack) != 1) {
        printf("test_pop_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_pop_2: PASS\n");
}


/* push single integer item to stack */
void test_push_1() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int value = 1;
    push(stack, &value, INT);
    if (stack->length != 1 || *(int *) stack->items->val != 1) {
        printf("test_push_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_push_1: PASS\n");
}

/* push two integer items to stack */
void test_push_2() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int values[] = {1, 2};
    push(stack, &values[0], INT);
    push(stack, &values[1], INT);
    if (
        stack->length != 2 ||
        *(int *) stack->items->val != 2 ||
        *(int *) stack->items->next->val != 1
    ) {
        printf("test_push_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_push_2: PASS\n");
}


/* check type of top item in stack of two integers */
void test_toptype_1() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int values[] = {1, 2};
    push(stack, &values[0], INT);
    push(stack, &values[1], INT);
    if (toptype(stack) != INT) {
        printf("test_toptype_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_toptype_1: PASS\n");
}


/* check type of top item in stack of 1 integer and 1 float*/
void test_toptype_2() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int i = 1;
    float f = 2;
    push(stack, &i, INT);
    push(stack, &f, FLOAT);
    if (toptype(stack) != FLOAT) {
        printf("test_toptype_2: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_toptype_2: PASS\n");
}


/* check value of top item in stack of two integers */
void test_topval_1() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    int values[] = {1, 2};
    push(stack, &values[0], INT);
    push(stack, &values[1], INT);
    if (*(int *) topval(stack) != 2) {
        printf("test_topval_1: FAILED\n");
        n_fail++;
        return;
    }
    printf("test_topval_1: PASS\n");
}


int main(int argc, char *argv[]) {
    printf("Running tests on stacks functions...\n\n");
    test_isempty_1();
    test_isempty_2();
    test_pop_1();
    test_pop_2();
    test_push_1();
    test_push_2();
    test_toptype_1();
    test_toptype_2();
    test_topval_1();
    printf("\nTests finished\n");
    printf("Number of failures: %d\n", n_fail);
    return 0;
}
