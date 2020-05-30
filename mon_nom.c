#include <stdio.h>
#include <string.h>

int main() {
    typedef char ch15 [16];
    ch15 name;
    strcpy(name, "Jonathan");
    printf("Hello %s!\n", name);
    return 0;
}
