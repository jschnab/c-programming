#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void push(double);
double pop();


int main(int argc, char *argv[]) {
    double op2;
    argv++;
    while (--argc > 0) {
        if ((*argv)[0] == '+') {
            push(pop() + pop());
            argv++;
        }
        else if ((*argv)[0] == '-') {
            op2 = pop();
            push(pop() - op2);
            argv++;
        }
        else if ((*argv)[0] == '*') {
            push(pop() * pop());
            argv++;
        }
        else if ((*argv[0]) == '/') {
            op2 = pop();
            if (op2 == 0.0) {
                printf("error: division by zero\n");
                return 1;
            }
            push(pop() / op2);
            argv++;
        }
        else {
            push(atof(*argv));
            argv++;
        }
    }
    printf("%.8g\n", pop());
    return 0;
}
