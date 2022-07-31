#include <stdio.h>

int get_line(char *line, int limit) {
    char c;
    int i;
    for (i = 0; (c = getchar()) != EOF && c != '\n' && i < limit; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i++] = '\n';
    }
    line[i] = '\0';
    return i;
}
