#include <stdio.h>

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c == ' ') {
            while ((c = getchar()) == ' ')
                ;
            if (c != EOF) {
                putchar(c);
            }
        }
    }
    return 0;
}
