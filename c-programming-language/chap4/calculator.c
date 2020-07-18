#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFSIZE 100
#define MAXOP 100  /* maximum size of operand or operator */
#define MAXVAL 100  /* maximum depth of val stack */
#define NUMBER '0' /* signal that a number was found */


char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;  /* free next position in buf */
int sp = 0;  /* next free stack position */
double val[MAXVAL];  /* value stack */


int getch(void);
int getop(char []);
double pop(void);
void push(double);
void ungetch(int);
int modulo(double, double);


int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;

            case '+':
                push(pop() + pop());
                break;

            case '*':
                push(pop() * pop());
                break;

            case '-':
                op2 = pop();
                push(pop() - op2);
                break;

            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
                
            case '%':
                op2 = pop();
                push(modulo(pop(), op2));
                break;

            case '\n':
                printf("%.8g\n", pop());
                break;

            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}


void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full can't push %g\n", f);
}


double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    /* '-' may be a negative sign so we ignore it here */
    if (!isdigit(c) && c != '.' && c != '-')
        return c;  /* not a number */
    
    i = 0;

    if (c == '-') {
        /* check the next character to see if it's part of a number */
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c;  /* negative number */

        /* subtraction sign */
        else {
            if (c != EOF)
                ungetch(c);
            return '-';
        }
    }

    if (isdigit(c))  /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')  /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}


/* get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


/* calculate modulo of two numbers */
int modulo(double a, double b) {
    int x = (int) a;
    int y = (int) b;
    return x - (x / y * y);
}
