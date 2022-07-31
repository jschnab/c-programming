#include <stdio.h>

#define MAXLINE 1000

void copy(char *, char *);
int get_line(char *, int);
void remove_blank(char *, int);

int main() {
    int n;
    char line[MAXLINE];
    while ((n = get_line(line, MAXLINE)) != 0) {
        remove_blank(line, n);
        if (line[0] != '\0' && line[0] != '\n') {
            printf("%s", line);
        }
    }
    return 0;
}

void copy(char *to, char *from) {
    int i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}

int get_line(char *s, int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = '\n';
        ++i;
    }
    s[i] = '\0';
    return i;
}

void remove_blank(char *line, int n) {
    int i = n - 1;
    int has_newline = 0;
    if (line[i] == '\n') {
        has_newline = 1;
        --i;
    }
    while ((line[i] == ' ' || line[i] == '\t') && i >= 0) { --i; }
    if (has_newline) { line[++i] = '\n'; }
    line[++i] = '\0';
}
