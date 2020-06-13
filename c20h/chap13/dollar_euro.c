#include <stdio.h>


#define RATE 0.89


int main() {
    double dollars = 0;
    while (dollars <= 10) {
        printf("%4.1f dollars = %.2f euros\n", dollars, dollars * RATE);
        dollars = dollars + 0.5;
    }
    return 0;
}
