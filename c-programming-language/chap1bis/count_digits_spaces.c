#include <stdio.h>

int main() {
    int c = 0, i, nwhite, nother;
    int ndigits[10];
    for (i = 0; i < 10; ++i) {
        ndigits[i] = 0;
    }
    nwhite = nother = 0;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            ++ndigits[c - '0'];
        }
        else if (c == ' ' || c == '\n' || c == '\t') {
            ++nwhite;
        }
        else {
            ++nother;
        }
    }
    printf("digits =");
    for (i = 0; i < 10; ++i) {
        printf(" %d", ndigits[i]);
    }
    printf(", white space = %d, other = %d\n", nwhite, nother);
    return 0;
}
