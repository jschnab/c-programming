#include <stdio.h>

int main() {
    long n;
    char c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            n++;
        }
    }
    printf("number of blanks, tabs, and newlines: %ld\n", n);
    return 0;
}
