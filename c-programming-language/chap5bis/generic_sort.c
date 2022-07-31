/* compile with:
 *
 * alloc.c
 * getline.c
 * readlines.c
 * str_cmp.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000  /* max number of lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
int str_cmp(char *s1, char *s2, int fold, int dir);
void writelines(char *lineptr[], int nlines);

void quicksort(
    void *lineptr[],
    int left,
    int right,
    int (*comp)(void *, void *, int, int),
    int rev,
    int fold,
    int dir
);
int numcmp(char *s1, char *s2, int, int);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;  /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */
    int rev = 0;  /* 1 if reverse sort */
    int fold = 0;  /* 1 to compare in a case-insensitive way */
    int dir = 0;  /* 1 to compare only alphanumeric characters and blanks */

    while (--argc > 0) {
        ++argv;
        if (strcmp(*argv, "-n") == 0) {
            numeric = 1;
        }
        if (strcmp(*argv, "-r") == 0) {
            rev = 1;
        }
        if (strcmp(*argv, "-f") == 0) {
            fold = 1;
        }
        if (strcmp(*argv, "-d") == 0) {
            dir = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort(
            (void **)lineptr,
            0,
            nlines - 1,
            (int (*)(void*, void*, int, int))(numeric ? numcmp : str_cmp),
            rev,
            fold,
            dir
        );
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* quicksort : sort v[left]..v[right] into increasing order */
void quicksort(
    void *v[],
    int left,
    int right,
    int (*comp)(void *, void *, int, int),
    int rev,
    int fold,
    int dir
) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (rev) {
            if ((*comp)(v[i], v[left], fold, dir) > 0)
                swap(v, ++last, i);
        }
        else
            if ((*comp)(v[i], v[left], fold, dir) < 0)
                swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1, comp, rev, fold, dir);
    quicksort(v, last + 1, right, comp, rev, fold, dir);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2, int fold /* not used */, int dir /* not used */) {
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
    void *tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
