#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *s = "3hello, world!";
    double val = atof(s);
    printf("%f\n", val);
    return 0;
}
