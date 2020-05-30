#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, guess;
    srand((unsigned) time(NULL));
    n = rand() % 100;

    printf("Guess a secret number between 0 and 99\n");
    do {
        printf("Enter your number: ");
        (void) scanf("%d%*c", &guess);
        if (guess < n)
            printf("It's higher\n");
        else if (guess > n)
            printf("It's lower\n");
    }
    while (guess != n);
    printf("You got it!\n");
    return 0;
}
