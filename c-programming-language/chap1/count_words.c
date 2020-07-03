#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0  /* outside a word */


int main() {
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }

    printf("Number lines: %d\n", nl);
    printf("Number words: %d\n", nw);
    printf("Number characters: %d\n", nc);

    return 0;
}
