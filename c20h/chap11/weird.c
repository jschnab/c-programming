#include <stdio.h>

int main() {
    // 'hello' won't be printed because printf() is stored
    // in a line buffer until a '\n' or fflush()
    printf("hello");
    while (1);
    return 0;
}
