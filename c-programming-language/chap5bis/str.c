#include <stdio.h>

/* copy t to s; array subscript version */
void astrcpy( char *s, char *t) {
    int i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}


/* copy t to s; pointer version 1 */
void pstrcpy1(char *s, char *t) {
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

/* copy t to s; pointer version 2 */
void strcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

void strncpy(char *s, char *t, int n) {
    while (n-- > 0 && (*s++ = *t++))
        ;
}

/* return <0 if s < t, 0 if s == t, > 0 if s > t */
int astrcmp(char *s, char *t) {
    int i;
    for (i = 0; s[i] == t[i]; ++i)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

/* return <0 if s < t, 0 if s == t, > 0 if s > t */
int strcmp(char *s, char *t) {
    for (;*s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int strncmp(char *s, char *t, int n) {
    if (n == 0)
        return 0;
    for (;n-- > 0 && *s == *t; s++, t++)
        ;
    if (n < 0) {
        s--;
        t--;
    }
    if (*s == *t)
        return 0;
    return *s - *t;
}

int main() {
    char s[] = "hello";
    char t[] = "helix";
    printf("%d\n", strncmp(s, t, 4));
    return 0;
}
