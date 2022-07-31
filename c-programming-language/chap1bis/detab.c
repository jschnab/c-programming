#include <stdio.h>

#define NSPACES 4

int main() {
    int i, c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (i = 0; i < NSPACES; ++i) { putchar(' '); }
        }
        else { putchar(c); }
    }
    return 0;
}
