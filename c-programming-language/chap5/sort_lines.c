#include <stdio.h>
#include <string.h>


#define ALLOCSIZE 10000  /* size of available space */
#define MAXLINES 5000  /* max number of lines to be sorted */
#define MAXLEN 1000  /* max length of an input line */


static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;  /* next free position, equivalent to
                                    static char *allocp = &allocbuf[0]; */
char *lineptr[MAXLINES];  /* pointer to text lines */


char *alloc(int);
int get_line(char *s, int max);
void qsort(char *lineptr[], int left, int right);
int readlines(char *lineptr[], int nlines);
void swap(char *v[], int i, int j);
void writelines(char *lineptr[], int nlines);


/* sort input lines */
int main() {
    int nlines;  /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


/* read input lines */
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


/* write output lines */
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
    /* could be written:
     * while (nlines-- > 0)
     *     printf("%s\n", *lineptr++);
     */
}


/* read a line from input */
int get_line(char *s, int max) {
    int i, c;

    for (i = 0; i<max-1 && (c = getchar()) != EOF && c != '\n'; i++)
        *(s + i) = c;

    if (c == '\n') {
        *(s + i) = c;
        i++;
    }

    *(s + i) = '\0';

    return i;
}


void qsort(char *v[], int left, int right) {
    int i, last;

    /* do nothing if array contains fewer than 2 elements */
    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);

}


void swap(char *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}


/* return pointer to n characters */
char *alloc(int n) {
    /* it fits */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;  /* old p */
    }

    /* not enough room */
    else
        return 0;  /* zero is never a valid address for data */
}
