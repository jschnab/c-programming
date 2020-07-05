#include <stdio.h>


unsigned get_bits(unsigned x, int p, int n);
unsigned set_bits(unsigned x, int p, int n, unsigned y);


int main() {
    /* should return 15 */
    printf("%d\n", set_bits(11, 3, 2, 11));

    /* should return 12 */
    printf("%d\n", set_bits(0, 3, 2, 3));

    /* should return 2 */
    printf("%d\n", set_bits(0, 2, 2, 1));

    /* should return 4 */
    printf("%d\n", set_bits(0, 3, 2, 1));

    /* should return 8 */
    printf("%d\n", set_bits(0, 3, 1, 1));

    return 0;
}


/* return the right-adjusted n-bit field of x that begins at position p */
unsigned get_bits(unsigned x, int p, int n) {
    /* ~ gives complement (convert 1 to 0 and vice versa so ~0 is all 1-bits
     * and (~0 << n) places zeros in the rightmost n bits */
    return (x >> (p+1-n)) & ~(~0 << n);
}


/* returns x with the n bits that begin at position p set to the rightmost
 * n bits of y, leaving the other bits unchanged */

unsigned set_bits(unsigned x, int p, int n, unsigned y) {
    return get_bits(x, p-n, p-n+1) | (get_bits(y, n-1, n) << (p-n+1));
}
