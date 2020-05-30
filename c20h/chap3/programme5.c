#include <stdio.h>

int main () {
    int a, b;
    printf("Calculator\n\n");
    printf("Value of a :\n");
    (void) scanf("%d", &a);
    printf("Value of b :\n");
    (void) scanf("%d", &b);
    printf("Value of a + b : %d\n", a + b);
    (void) getchar();
    return 0;
}
