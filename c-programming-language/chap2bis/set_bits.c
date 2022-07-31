#include <stdio.h>

unsigned set_bits(unsigned, int, int, unsigned);

int main() {
    printf("%d\n", set_bits(0, 3, 0, 15));
    return 0;
}

unsigned set_bits(unsigned x, int p, int n, unsigned y) {
    return x | (y & (((1 << n) - 1) << (p - n + 1)));
}
