#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define PRINTLINES 10

char *lineptr[MAXLINES];

char *alloc(int);
int get_line(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int start, int nlines);

int main(int argc, char *argv[]) {
    int total_lines;
    int nlines = PRINTLINES;

    if (--argc > 0 && (*++argv)[0] == '-') {
        nlines = atoi(*argv + 1);
    }

    if((total_lines = readlines(lineptr, MAXLINES)) >= 0) {
        if (nlines > total_lines)
            nlines = total_lines;
        writelines(lineptr, total_lines - nlines, nlines);
    } else {
        printf("error: input too big\n");
        return 1;
    }
    return 0;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';  /* delete newline characters */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int start, int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *(lineptr++ + start));
}
