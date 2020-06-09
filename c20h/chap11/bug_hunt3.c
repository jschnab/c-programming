#include <stdio.h>
#include <string.h>

int main() {
    int i;
    int * p = &i;
    *p = 123;
    printf("\n I am here...\n");
}
