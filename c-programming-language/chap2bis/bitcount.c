#include <stdio.h>

int bitcount(unsigned x) {
    int count = 0;
    while (x != 0) {
        x &= x - 1;
        ++count;
    }
    return count;
}

int main() {
    int x = 13;
    printf("bitcount(%d) = %d\n", x, bitcount(x));
    return 0;
}
