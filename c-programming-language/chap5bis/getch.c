#include <stdio.h>

#define SIZE 1000  /* size of the stack */

static int stack[SIZE];
static int sp;  /* index of next available stack position */

int getch(void) {
    return (sp > 0) ? stack[--sp] : getchar();
}

void ungetch(int c) {
    if (sp < SIZE)
        stack[sp++] = c;
    else
        printf("error: stack full\n");
}
