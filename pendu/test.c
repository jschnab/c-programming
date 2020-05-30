#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char word[6] = "hello";
    printf("Please enter a letter : ");
    char c = getchar();
    while (getchar() != '\n');
    //char *found = NULL;
    //found = strchr(word, c);
    //printf("%s\n", found);
    if (strchr(word, c) != NULL)
        printf("Letter found!\n");
    else
        printf("Letter not found...\n");
    return 0;
}
