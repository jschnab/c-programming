#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);


/* get next integer from input into *pn */
int getfloat(double *pn) {
    int c, c2, sign, power = 1;
    while (isspace(c = getch()))  /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);  /* not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {
        c2 = c;
        c = getch();
    }

    /* make sure that a + or - with no following digit
     * is not treated as a representation of zero */
    if (!isdigit(c)) {
        ungetch(c2);
        if (c != EOF)
            ungetch(c);
        return 0;
    }

    /* get integer part */
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = *pn * 10 + c - '0';
    }

    /* get fractional part */
    if (c == '.') {
        c = getch();
        for (; isdigit(c); c = getch()) {
            *pn = *pn * 10 + c - '0';
            power *= 10;
        }
    }
    *pn = *pn * sign / power;;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main() {
    double n;
    getfloat(&n);
    printf("input = %f\n", n);
    return 0;
}
