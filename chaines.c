#include <stdio.h>
#include <string.h>

int str_len (char str[]);

int main (int argc, char *argv[]) {
    char nom[100];
    printf("Please enter your name : ");
    scanf("%c%*c", nom);
    const int l = str_len(nom);
    printf("The string \"%s\" has length %d\n", nom, l);
    return 0;
}

int str_len (char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
