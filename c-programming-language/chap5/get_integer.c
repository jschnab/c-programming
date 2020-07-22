#include <ctype.h>


int getch(void);
void ungetch(int);
int getint(int *);


int main() {
    return 0;
}


/* get next integer from input into pointer */
int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()))  /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && != '-') {  /* not a number */
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}
