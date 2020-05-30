#include <stdio.h>

void convert_time(int *h, int *m);

int main(int argc, char *argv[]) {
    int heures = 0;
    int minutes = 90;

    convert_time(&heures, &minutes);

    printf("heures : %d\nminutes : %d\n", heures, minutes);

    return 0;
}

void convert_time (int *h, int *m) {
    *h = *m / 60;
    *m = *m % 60;
}
