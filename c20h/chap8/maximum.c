#include <stdio.h>

static int maximum(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    int a, b;
    printf("enter a number: ");
    (void) scanf("%d%*c", &a);
    printf("enter another number: ");
    (void) scanf("%d%*c", &b);
    printf("the greater is %d\n", maximum(a, b));
    return 0;
}
