#include <stdio.h>


int main() {
    char s[] = "hello world";
    char *p = s;
    printf("string s = %s\n", s);
    printf("pointer s = %p\n", s);
    printf("string p = %s\n", p);
    printf("pointer p = %p\n", p);

    s[4] = 'p';
    printf("string s = %s\n", s);

    *(p+4) = 'o';
    printf("string s = %s\n", s);

    return 0;
}
