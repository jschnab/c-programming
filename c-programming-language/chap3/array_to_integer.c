#include <stdio.h>
#include <ctype.h>


int atoi(char s[]);


int main() {
    char a[] = "  +33 ";
    char b[] = "-2";
    printf("%s + %s = %d\n", a, b, atoi(a) + atoi(b));
    return 0;
}


int atoi(char s[]) {
    int i;

    for (i = 0; isspace(s[i]); i++)
        ;

    int sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    int n;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');

    return sign * n;
}
