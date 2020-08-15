#include <stdio.h>
#include <stdlib.h>


#define MAXLINE 1000


char *myfgets(char *, int, FILE *);
int myfputs(char *, FILE *);


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: ./getsputs <file name>\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "file '%s' failed to open\n", argv[1]);
        exit(1);
    }

    char line[MAXLINE];
    while (myfgets(line, MAXLINE, fp)) {
        fprintf(stderr, "line: ");
        myfputs(line, stdout);
    }
    fclose(fp);
    return 0;
}


char *myfgets(char *s, int n, FILE *input) {
    register int c;
    register char *cs;
    cs = s;
    while (--n > 0 && (c = getc(input)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}


int myfputs(char *s, FILE *output) {
    int c;
    while ((c = *s++))
        putc(c, output);
    return ferror(output) ? EOF : 0;
}
