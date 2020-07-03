#include <stdio.h>


int main() {
    int nc;
    for (nc = 0; getchar() != EOF; ++nc);
    printf("number characters: %d\n", nc);
    return 0;
}
