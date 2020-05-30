#include <stdio.h>
#include <math.h>

int main() {
    int i, j, n, width;
    n = 10;
    width = 3;

    // print top of the tree
    for (i=0; i<n; i++) {
        for (j=0; j<n-i-1; j++)
            printf(" ");
        for (j=0; j<2*i+1; j++)
            printf("*");
        for (j=0; j<n-i-1; j++)
            printf(" ");
        printf("\n");
    }

    // print the trunk
    for (i=0; i<width; i++) {
        for (j=0; j<n-width+1; j++)
            printf(" ");
        for (j=0; j<width; j++)
            printf("@");
        for (j=0; j<n-width+1; j++)
            printf(" ");
        printf("\n");
    }
    return 0;
}
