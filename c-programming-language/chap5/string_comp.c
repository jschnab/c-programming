#include <stdio.h>


int strcmp_array(char *, char *);
int strcmp_pointer(char *, char *);


int main() {
    char s[] = "hello";
    char t[] = "help";
    printf("strcmp (%s, %s) = %d\n", s, t, strcmp_array(s, t));

    char u[] = "hello";
    char v[] = "world";
    printf("strcmp (%s, %s) = %d\n", u, v, strcmp_array(u, v));

    return 0;
}


int strcmp_array(char *s, char *t) {
    int i;
    for (i = 0; s[i] == t[i]; i++) {
        if (s[i] == '\0')
            return 0;
    }
    return s[i] - t[i];
}


int strcmp_pointer(char *s, char *t) {
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
