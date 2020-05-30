#include <stdio.h>

int main() {
    int i;
    int *p = &i;
    char c;

    printf("Hello world!\n");
    printf("Size of int : %ld bytes\n", sizeof(int));
    printf("Size of char : %ld bytes\n", sizeof(char));
    printf("Size of short : %ld bytes\n", sizeof(short));
    printf("Size of long : %ld bytes\n", sizeof(long));
    printf("Size of float : %ld bytes\n", sizeof(float));
    printf("Size of double : %ld bytes\n", sizeof(double));
    printf("Size of long double : %ld bytes\n", sizeof(long double));

    printf("\n");
    printf("Please enter a number between 1 and 10 : ");
    scanf("%d%*c", &i);
    printf("Please enter a character : ");
    scanf("%c", &c);
    *p = *p + 1; // increment value of i
    printf("value of i+1 : %d\naddress of i : %p\nvalue of p : %p\naddress of p : %p\n",\
            i, &i, p, &p);
    printf("character c : %c\n", c);
    return 0;
}

