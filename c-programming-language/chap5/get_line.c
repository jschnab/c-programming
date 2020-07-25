#include <stdio.h>


#define LINELENGTH 100


int get_line(char *, int);


int main() {
    char line[LINELENGTH];
    int n = get_line(line, LINELENGTH);
    printf("line (length=%d): %s\n", n, line);
    return 0;
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
