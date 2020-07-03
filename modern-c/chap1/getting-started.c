#include <stdio.h>
#include <stdlib.h>


int main(void) {
    double A[5] = {
        [0] = 9.0,
        [1] = 2.0,
        [4] = 3.E+25,
        [3] = .00007l
    };

    for (size_t i = 0; i < 5; ++i) {
        printf("element %zu is %g, \tits square is %g\n",
            i,
            A[i],
            A[i] * A[i]
        );
    }

    return EXIT_SUCCESS;
}
