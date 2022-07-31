#include <stdio.h>

void strcat(char *s, char *t) {
    while (*s++)
        ;
    s--;
    while (*s++ = *t++)
        ;
}

void strncat(char *s, char *t, int n) {
    while (*s++)
        ;
    s--;
    while (n-- > 0 && (*s++ = *t++))
        ;
}

int main() {
    char s[20] = "hello";
    char t[] = "mountain";
    printf("s = %s\n", s);
    strncat(s, t, 16);
    printf("s = %s\n", s);
    return 0;
}
