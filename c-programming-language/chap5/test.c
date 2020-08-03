#include <stdio.h>


int main(int argc, char *argv[]) {
    char *lines[2] = {"hello", "world"};
    printf("address of lines[0] = %p\n", lines[0]);
    printf("lines[0] = %s\n", lines[0]);
    printf("address of lines[1] = %p\n", lines[1]);
    printf("lines[0] = %s\n", lines[1]);
    printf("swapping words\n");
    char *tmp = lines[0];
    lines[0] = lines[1];
    lines[1] = tmp;
    printf("address of lines[0] = %p\n", lines[0]);
    printf("lines[0] = %s\n", lines[0]);
    printf("address of lines[1] = %p\n", lines[1]);
    printf("lines[0] = %s\n", lines[1]);
    return 0;
}
