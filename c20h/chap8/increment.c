#include <stdio.h>


static void increment(int * i) {
    (*i)++;
}


int main() {
    int a = 1;
    printf("a = %d\n", a);
    increment(&a);
    printf("a = %d\n", a);

    return 0;
}
