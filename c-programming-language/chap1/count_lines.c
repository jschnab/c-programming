#include <stdio.h>


int main() {
    int c, nl = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
    }
    printf("number of lines: %d\n", nl);
    return 0;
}
