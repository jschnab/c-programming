#include <stdio.h>
#include <string.h>

#define MAXLINES 5000  /* max number of lines to be sorted */
#define MAXLEN 1000  /* max length of any input line */

char *lineptr[MAXLINES];  /* pointers to text lines */

char *alloc(int);
int get_line(char *, int);
void qsort(char *lineptr[], int left, int right);
int readlines(char *lineptr[], int nlines);
void swap(char *v[], int i, int j);
void writelines(char *lineptr[], int nlines);

int main() {
    int nlines;  /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';  /* delete newlines */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right) {
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
