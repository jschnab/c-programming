#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define POW '1'
#define SIN '2'
#define COS '3'
#define EXP '4'
#define MOD '5'
#define UNKNOWN '6'


int getop(char *, char *);
int is_number(char *);
double pop(void);
void push(double);
double top(void);


int sp = 0;
double val[MAXVAL];


int main(int argc, char *argv[]) {
    /*
    argv++;
    printf("%s is %sa number\n", *argv, (is_number(*argv)) ? "" : "not ");
    */
    int type;
    double op2;
    char s[MAXOP];

    if (argc < 2) {
        printf("Usage: %s [arg ...]\n", *argv);
        exit(1);
    }

    while (--argc > 0 && (type = getop(s, *++argv)) != EOF) {
        switch (type) {
            case NUMBER:
                //printf("got number\n");
                push(atof(s));
                break;
            case '+':
                //printf("got +\n");
                push(pop() + pop());
                break;
            case '-':
                //printf("got -\n");
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                //printf("got *\n");
                push(pop() * pop());
                break;
            case '/':
                //printf("got /\n");
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else {
                    printf("error: zero divisor\n");
                    exit(1);
                }
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else {
                    printf("error: zero divisor\n");
                    exit(1);
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
            default:
                printf("error: unknown command %s\n", s);
                exit(1);
        }
        //printf("top: %f\n", top());
    }
    if (sp == 1)
        printf("%.8g\n", pop());
    return 0;
}


double pop(void) {
    if (sp > 0)
        return val[--sp];
    printf("error: stack empty\n");
    return 0.0;
}


void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
        return;
    }
    printf("error: stack full\n");
    exit(1);
}


int getop(char *s, char *arg) {
    int ret;
    printf("arg is: %s\n", arg);

    /* check if arg is number */
    if (is_number(arg)) {
        printf("arg is a number\n");
        ret = NUMBER;
    }

    /* check if arg is simple operator */
    else if (
        strcmp("+", arg) == 0 ||
        strcmp("-", arg) == 0 ||
        strcmp("*", arg) == 0 ||
        strcmp("/", arg) == 0 ||
        strcmp("%", arg) == 0
    ) {
        printf("arg is an operator\n");
        ret = arg[0];
    }

    else if (strcmp("pow", arg) == 0)
        ret = POW;

    else if (strcmp("sin", arg) == 0)
        ret = SIN;

    else if (strcmp("cos", arg) == 0)
        ret = COS;

    else if (strcmp("exp", arg) == 0)
        ret = EXP;

    else
        ret = UNKNOWN;

    strcpy(s, arg);
    return ret;
}


double top(void) {
    return val[sp - 1];
}


int is_number(char *s) {
    char c;
    if (*s == '.' && *(s+1) == '\0')
        return 0;
    if (*s == '-')
        s++;
    if (!isdigit(c = *s++) && c != '.')
        return 0;
    while ((c = *s++) != '.' && c != '\0')
        if (!isdigit(c))
            return 0;
    if (c == '\0')
        return 1;
    while ((c = *s++) != '\0')
        if (!isdigit(c))
            return 0;
    return 1;
}
