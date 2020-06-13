#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;
    int * p;
    printf("enter the number of values: ");
    (void) scanf("%d%*c", &x);
    p = malloc(x * sizeof(int));
    free(p);
    return 0;
}
