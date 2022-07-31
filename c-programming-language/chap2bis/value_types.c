#include <locale.h>
#include <stdio.h>


int main() {
    setlocale(LC_NUMERIC, "");
    printf("size of char: %ld\n", sizeof(char));
    printf("size of short: %ld\n", sizeof(short));
    printf("size of int: %ld\n", sizeof(int));
    printf("size of long: %ld\n", sizeof(long));

    long int s = 1;
    for (size_t i = 0; i < sizeof(char) * 8; ++i) {
        s *= 2;
    }
    printf("max value of unsigned char: %'ld\n", s - 1);

    s = 1;
    for (size_t i = 0; i < sizeof(char) * 8; ++i) {
        s *= 2;
    }
    printf("max value of signed char: %'ld\n", s / 2 - 1);

    s = 1;
    for (size_t i = 0; i < sizeof(short) * 8; ++i) {
        s *= 2;
    }
    printf("max value of unsigned short: %'ld\n", s - 1);

    s = 1;
    for (size_t i = 0; i < sizeof(short) * 8; ++i) {
        s *= 2;
    }
    printf("max value of signed short: %'ld\n", s / 2 - 1);

    s = 1;
    for (size_t i = 0; i < sizeof(int) * 8; ++i) {
        s *= 2;
    }
    printf("max value of unsigned int: %'ld\n", s - 1);

    s = 1;
    for (size_t i = 0; i < sizeof(int) * 8; ++i) {
        s *= 2;
    }
    printf("max value of signed signed int: %'ld\n", s / 2 - 1);

    printf("max value of unsigned long: %'lld\n", (((1LL << (sizeof(long) * 8 - 2)) - 1) * 2) + 1);

    s = 1;
    for (size_t i = 0; i < sizeof(long) * 8; ++i) {
        s *= 2;
    }
    printf("max value of signed long: %'lld\n", s << 64 / 2 - 1);

    return 0;
}
