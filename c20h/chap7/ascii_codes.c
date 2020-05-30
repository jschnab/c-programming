#include <stdio.h>

int main() {
    int i, j;
    printf("ASCII codes\n-----------\n\n");
    for (i=32; i<128; i+=8) {
        for (j=0; j<7; j++)
            printf("%3d : '%c'   ", i+j, i+j);
        printf("%3d : '%c'\n", i+j, i+j);
    }
    return 0;
}
