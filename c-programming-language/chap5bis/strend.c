#include <stdio.h>

int strend(char *s, char *t) {
    char *u = s;
    while (*(s + 1))
        s++;
    char *v = t;
    while (*(t + 1))
        t++;
    while (*s == *t && s != u && v != t) {
        s--;
        t--;
    }
    if (*s == *t && v == t)
        return 1;
    return 0;
}

int main() {
    printf("%d\n", strend("hello", "lo"));
    printf("%d\n", strend("hello", "gloubiboulga"));
    return 0;
}
