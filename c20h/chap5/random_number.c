#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    srand(time(NULL));
    n = rand() % 100;
    printf("Random number: %d\n", n);
    return 0;
}
