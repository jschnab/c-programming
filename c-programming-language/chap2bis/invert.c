#include <stdio.h>

unsigned invert(unsigned, int, int);

int main() {
    printf("%d\n", invert(10, 3, 2));
    return 0;
}

unsigned invert(unsigned x, int p, int n) {
    return x ^ (((1 << n) - 1) << (p - n + 1));
}
