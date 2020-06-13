#include <stdio.h>

static void two_times(int * i) {
    *i = 2 * (*i);
}

int main () {
    int x = 3;
    printf("i = %d\n", x);
    int * y = &x;
    two_times(y);
    printf("i = %d\n", x);
    return 0;
}
