#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>  /* for atof() */


#define BUFSIZE 100
#define MAXOP 100   /* max size of operand or operator */
#define MAXVAL 100  /* maximum depth of stack */
#define NUMBER '0'  /* signal that a number was found */
#define POW '1'     /* signal that power function was found */
#define SIN '2'     /* signal that sine function was found */
#define COS '3'     /* signal that cosine function was found */
#define EXP '4'     /* signal that exponential function was found */


void clear(void);
void duplicate(void);
int getch(void);
int getop(char *);
int modulo(int, int);
double pop(void);
void push(double);
void swap(void);
double top(void);
void ungetch(int);


char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buffer */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */


/* reverse Polish calculator */
int main () {
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
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                    push((int)pop() % (int)op2);
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case SIN:
                push(sin(pop()));
                break;
            case COS:
                push(cos(pop()));
                break;
            case EXP:
                push(exp(pop()));
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


/* push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else {
        printf("error: stack full, can't push %g\n", f);
    }
}


/* pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


/* duplicate stack */
void duplicate(void) {
    if (sp >= MAXVAL / 2) {
        printf("error: stack too full to duplicate\n");
        return;
    }
    int i = 0, n = sp;
    while (i < n)
        val[sp++] = val[i++];
}


/* get top element of the stack */
double top(void) {
    if (sp == 0) {
        printf("error: stack empty\n");
        return 0.0;
    }
    return val[sp - 1];
}


/* clear the stack */
void clear(void) {
    sp = 0;
}


/* swap top two elements of stack */
void swap(void) {
    if (sp < 2) {
        printf("error: not enough elements in stack\n");
        return;
    }
    double tmp = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = tmp;
}


/* get next operator or numeric operand */
int getop(char *s) {
    int i = 0, c, c2, c3;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        c2 = getch();
        if (!(c == '-' && isdigit(c2))) {
            c3 = getch();
            if (c == 'p' && c2 == 'o' && c3 == 'w') {
                return POW;
            }
            else if (c == 's' && c2 == 'i' && c3 == 'n') {
                return SIN;
            }
            else if (c == 'c' && c2 == 'o' && c3 == 's') {
                return COS;
            }
            else if (c == 'e' && c2 == 'x' && c3 == 'p') {
                return EXP;
            }
            else {
                ungetch(c3);
                ungetch(c2);
                return c;
            }
        }
        c = s[++i] = c2;
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


int modulo(int a, int b) {
    return a - (b * (a / b));
}
