#include <stdio.h>


#define STACKDEPTH 100  /* maximum depth of stack */


double pop(void);
void push(double);
void top(void);
void duplicate_top(void);
void swap_top(void);
void clear(void);


double stack[STACKDEPTH];
int sp = 0;  /* next free stack position */


int main() {
    push(3.14);
    swap_top();
    push(6.28);
    push(12.56);

    top();
    swap_top();
    top();
    duplicate_top();

    clear();

    while (sp > 0)
        printf("popped: %f\n", pop());

    top();

    return 0;
}


double pop(void) {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


void push(double val) {
    if (sp < STACKDEPTH)
        stack[sp++] = val;
    else
        printf("error: stack full can't push\n");
}


/* print top element from stack */
void top(void) {
    if (sp > 0)
        printf("top: %g\n", stack[sp-1]);
    else
        printf("error: stack empty\n");
}


/* duplicate top element from stack */
void duplicate_top(void) {
    if (sp > 0)
        push(stack[sp-1]);
    else
        printf("error: stack empty can't duplicate top\n");
}


/* swap top two elements from stack */
void swap_top(void) {
    if (sp > 1) {
        double tmp = stack[sp-1];
        stack[sp-1] = stack[sp-2];
        stack[sp-2] = tmp;
    }
    else
        printf("error: stack too small can't swap\n");
}


/* clear the stack */
void clear(void) {
    sp = 0;
}
