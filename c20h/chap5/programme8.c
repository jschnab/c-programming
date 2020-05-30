#include <stdio.h>

int main() {
    char car = ' ';
    int exit = 0;
    do {
        printf("Enter 'S' to exit\n");
        car = getchar();
        exit = ((car == 's') || (car == 'S'));
    }
    while (exit == 0);
    return 0;
}
