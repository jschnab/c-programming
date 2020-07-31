#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ALLOCSIZE 10000  /* size of the available space */
#define MAXLINES 5000  /* maximum number of lines to be sorted */
#define MAXLEN 1000  /* maximum length of an input line */


char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;
char *lineptr[MAXLINES]; /* pointers to text lines */


char *alloc(int);
int get_line(char *s, int max);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void quicksort(
    void *lineptr[],
    int left,
    int right,
    int (*comp)(void *, void *)
);
int numcmp(char *, char *);
void swap(void *v[], int i, int j);


int main(int argc, char *argv[]) {
    int nlines;  /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort(
            (void **) lineptr,
            0,
            nlines-1,
            (int (*)(void*,void*))(numeric ? numcmp : strcmp)
        );
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}


void quicksort(
    void *v[],
    int left,
    int right,
    int (*comp)(void *, void *)
) {
    int i, last;
    
    /* do nothing if array contains fewer than two elements */
    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}


int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}


void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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


void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}


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


char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n ;
        return allocp - n;
    }
    else
        return 0;
}
