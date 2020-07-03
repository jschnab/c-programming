#include <stdio.h>


int power(int base, int n);


int main() {
    int a = 2;
    int b = 3;

    printf("%d^%d = %d\n", a, b, power(a, b));

    return 0;
}


int power(int base, int n) {
    /* function arguments are passed by value */
    /* so the loop modifies n only in the function's scope */
    int p = 1;
    for (; n > 0; --n)
        p *= base;
    return p;
}
