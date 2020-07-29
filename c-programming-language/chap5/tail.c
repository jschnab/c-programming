#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ALLOCSIZE 10000
#define MAXLINES 5000
#define MAXLEN 1000


char allocbuf[ALLOCSIZE];  /* storage for alloc */
char *allocp = allocbuf;  /* next free position */


char *alloc(int);
int get_line(char *, int);
char *lineptr[MAXLINES];


int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);


int main(int argc, char *argv[]) {
    if (--argc > 1) {
        printf("Usage: tail -n <number lines>\n");
        return 1;
    }

    int n = atoi(*++argv);

    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        for (int i = 0; i < nlines; i++) {
            if (i >= nlines - n)
                printf("%s\n", lineptr[i]);
        }
    }

    return 0;
}


int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';  /* delete newline character */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}


int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}


/* return pointer to n characters */
char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {  /* it fits */
        allocp += n;
        return allocp -n;  /* old p */
    }
    else  /* not enough room */
        return 0;
}
