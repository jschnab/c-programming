#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);


/* get next integer from input into *pn */
int getint(int *pn) {
    int c, c2, sign;
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

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = *pn * 10 + c - '0';
    }
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main() {
    int n;
    getint(&n);
    printf("input = %d\n", n);
    return 0;
}
