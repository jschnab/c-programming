#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int random_number;
    int i = 0;
    int n_odd = 0;
    int n_even = 0;

    srand((unsigned) time(NULL));

    do {
        random_number = rand();
        if (random_number % 2 == 0)
            n_even++;
        else
            n_odd++;
        i++;
    }
    while (i < 1000);

    printf("Proportion of odd numbers: %f\n", (float) n_odd / i);
    printf("Proportion of even numbers: %f\n", (float) n_even / i);
    return 0;
}
