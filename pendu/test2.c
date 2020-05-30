#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char word[10] = "pendu";
    int i = 0;
    for (i = 0; i < strlen(word); i++)
        word[i] = '*';
    printf("%s\n", word);
    return 0;
}
