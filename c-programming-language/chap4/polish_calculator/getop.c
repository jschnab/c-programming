#include <stdio.h>
#include <ctype.h>
#include "calc.h"


int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    /* '-' could be a negative sign so we ignore it here */
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


/* calculate modulo of two numbers */
int modulo(double a, double b) {
    int x = (int) a;
    int y = (int) b;
    return x - (x / y * y);
}
