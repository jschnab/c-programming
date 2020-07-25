#include <stdio.h>


int string_length(char *);


int main() {
    char *s = "hello";
    printf("length of '%s' = %d\n", s, string_length(s));
    return 0;
}


int string_length(char *s) {
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}
