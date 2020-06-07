#include <stdio.h>
#include <string.h>


int main() {
    int i;
    char characters[27];

    for (i=0; i<26; i++)
        characters[i] = i + 65;
    characters[26] = '\0';

    printf("length string: %ld\n", sizeof(characters) / sizeof(characters[0]));
    
    for (i=0; i<strlen(characters); i++)
        printf("character %d = %c\n", i, characters[i]);

    printf("string: %s\n", characters);

    return 0;
}
