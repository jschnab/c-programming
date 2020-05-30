#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void emptyBuffer ();
int readString (char *str, int length);
long readLong ();
double readDouble ();

int main (int argc, char *argv[]) {

    printf("Please enter a number : ");
    long l = readLong();
    printf("You entered %ld\n\n", l);

    printf("Please enter a decimal : ");
    double d1 = readDouble();
    printf("Please enter another decimal : ");
    double d2 = readDouble();
    printf("%.3f + %.3f = %.3f\n", d1, d2, d1 + d2);

    return 0;
}

void emptyBuffer () {
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int readString (char *str, int length) {

    char *newLinePosition = NULL;

    if (fgets(str, length, stdin) != NULL) {

        newLinePosition = strchr(str, '\n');

        if (newLinePosition != NULL)
            newLinePosition = '\0';

        else
            emptyBuffer();

        return 1;
    }
    else {
        emptyBuffer();

        return 0;
    }
}

long readLong () {

    char numbers[100];

    if (readString(numbers, 100))
        return strtol(numbers, NULL, 10);
    else
        return 0;
}

double readDouble () {

    char numbers[100];

    if (readString(numbers, 100))
        return strtod(numbers, NULL);
    else
        return 0;
}
