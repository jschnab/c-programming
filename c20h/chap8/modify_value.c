#include <stdio.h>

int main() {
    int number = 10;
    printf("number holds %d\n", number);
    int * ptr_number;
    ptr_number = &number;
    *ptr_number = 35;
    printf("now number holds %d\n", number);
    return 0;
}
