#include <stdio.h>
#include <string.h>

int main() {
    int i;
    char word[] = "!deggubed si demmargorp eht";
    for (i = strlen(word); i > 0; i--)
        printf("%c", word[i]);
    printf("\n");
    return 0;
}
