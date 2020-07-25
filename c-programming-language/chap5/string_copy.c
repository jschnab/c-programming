#include <stdio.h>


void strcpy_array(char *, char *);
void strcpy_pointer(char *, char *);


int main() {
    char t[] = "hello there!";
    char s[13];
    strcpy_array(s, t);
    printf("s = %s\n", s);

    char u[] = "goodbye cruel world";
    char v[20];
    strcpy_pointer(v, u);
    printf("v = %s\n", v);

    return 0;
}


/* array version */
void strcpy_array(char *s, char *t) {
    int i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}


/* pointer version */
void strcpy_pointer(char *s, char *t) {
    while (*s++ = *t++)
        ;
}
