#include <stdio.h>
#include <ctype.h>

int comp(char c1, char c2, int fold) {
    if (fold) {
        c1 = tolower(c1);
        c2 = tolower(c2);
    }
    return c1 - c2;
}

int str_cmp(char *s1, char *s2, int fold, int dir) {
    char c1 = *s1;
    char c2 = *s2;
    int skip;
    while (1) {
        skip = 0;
        if (c1 == '\0' || c2 == '\0')
            break;
        if (dir && !isalnum(c1) && c1 != ' ' && c1 != '\t' && c1 != '\n') {
            c1 = *++s1;
            skip = 1;
        }
        if (dir && !isalnum(c2) && c2 != ' ' && c2 != '\t' && c2 != '\n') {
            c2 = *++s2;
            skip = 1;
        }
        if (skip)
            continue;
        if (comp(c1, c2, fold) != 0)
            break;
        c1 = *++s1;
        c2 = *++s2;
    }
    return c1 - c2;
}

/*
int main() {
    char *s1 = "/h&e'l-l(a@";
    char *s2 = ",h.e?l+l)o*";
    printf("%d\n", str_cmp(s1, s2, 0, 1));
    return 0;
}
*/
