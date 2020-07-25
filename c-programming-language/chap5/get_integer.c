#include <stdio.h>
#include <ctype.h>


#define BUFSIZE 100


int getch(void);
void ungetch(int);
int getint(int *);


static char buf[BUFSIZE];
static int bufp = 0;


int main() {
    int n, c;
    c = getint(&n);
    printf("n = %d, c = %d\n", n, c);
    return 0;
}


/* get next integer from input into pointer */
int getint(int *pn) {
    int c;

    while (isspace(c = getch()))  /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {  /* not a number */
        ungetch(c);
        return 0;
    }

    int sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int d = c;  /* remember sign char */
        if (!isdigit(c = getch())) {
            if (c != EOF)
                ungetch(c);  /* push back non-digit */
            ungetch(d);  /* push back sign char */
            return d;  /* return sign char */
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
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
