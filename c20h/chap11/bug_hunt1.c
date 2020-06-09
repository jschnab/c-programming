#include <stdio.h>

int main() {
    int i, sum;
    for (i=0; i<10; i++) {
        printf("i = %d\n", i);
        sum += i;
    }
    printf("Mean = %f\n", (float)sum / (float)i);
    return 0;
}
