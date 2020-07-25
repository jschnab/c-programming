#include <stdio.h>
#include <string.h>


void string_cat(char *, char*);


int main() {
    char a[20] = "hello";
    char b[20] = "world";
    printf("before concat: a = %s\n", a);
    string_cat(a, b);
    printf("after concat: a = %s\n", a);
    return 0;
}



/* concatenate t to the end of s */
void string_cat(char *s, char *t) {
    int i, j;
    i = j = 0;

    /* find the end of s */
    while (*(s+i) != '\0')
        i++;

    /* copy t into s */
    while ((*(s + i++) = *(t + j++)) != '\0')
        ;
}
