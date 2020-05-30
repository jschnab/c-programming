#include <stdio.h>

int main() {
    int val1, val2;
    printf("Enter value 1: ");
    (void) scanf("%d", &val1);
    printf("Enter value 2: ");
    (void) scanf("%d", &val2);
    if (val1 > val2)
        printf("Higher value is %d\n", val1);
    else
        printf("Higher value is %d\n", val2);
    return 0;
}
