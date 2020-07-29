#include <stdio.h>


#define LENGTH 100


int sp = 0;
double stack[LENGTH];


void push(double x) {
    if (sp < LENGTH)
        stack[sp++] = x;
    else
        printf("error: stack full can't push %g\n", x);
}


double pop() {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: can't pop stack empty\n");
        return 0.0;
    }
}
