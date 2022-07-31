#include <stdio.h>

int any(char *, char *);

int main() {
    char *s1 = "hello";
    char *s2 = "world";
    printf("%d\n", any(s1, s2));
    return 0;
}

int any(char *a, char *b) {
    int i, j;
    for (j = 0; b[j] != '\0'; ++j) {
        for (i = 0; a[i] != '\0'; ++i) {
            if (a[i] == b[j]) {
                return i;
            }
        }
    }
    return -1;
}
