#include <stdio.h>


unsigned get_bits(unsigned x, int p, int n);


int main() {
    /* should print 5 */
    printf("%d\n", get_bits(42, 3, 3));

    int p = 3;
    int n = 2;
    /* should print 3 */
    printf("%d\n", get_bits(11, p-n, p-n+1));

    /* should return 12 */
    printf("%d\n", get_bits(11, n-1, n) << n);
    return 0;
}


/* return the right-adjusted n-bit field of x that begins at position p */
unsigned get_bits(unsigned x, int p, int n) {
    /* ~ gives complement (convert 1 to 0 and vice versa so ~0 is all 1-bits
     * and (~0 << n) places zeros in the rightmost n bits */
    return (x >> (p+1-n)) & ~(~0 << n);
}
