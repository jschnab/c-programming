#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c = 0, state = OUT, i = 0, j = 0, wl = 0;
    int count_lengths[10];
    for (i = 0; i < 10; ++i) {
        count_lengths[i] = 0;
    }
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                ++count_lengths[wl];
                wl = 0;
            }
            state = OUT;
        }
        else {
            state = IN;
            ++wl;
        }
    }
    for (i = 1; i < 10; ++i) {
        printf("%d ", i);
        for (j = 0; j < count_lengths[i]; ++j) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
