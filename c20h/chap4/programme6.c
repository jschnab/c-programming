#include <stdio.h>
#include <math.h>

int main () {
    float a, b;
    printf("Value of a:\n");
    (void) scanf("%f", &a);
    printf("Value of b:\n");
    (void) scanf("%f", &b);
    printf("Hypotenuse: %f\n", sqrt(a*a + b*b));
    return 0;
}
