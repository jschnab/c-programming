#include <stdio.h>


void squeeze(char s[], char t[]);


int main() {
    char string1[] = "jonathan";
    char string2[] = "jaynee";
    squeeze(string1, string2);
    printf("squeezed: %s\n", string1);
    return 0;
}


/* delete from s all characters present in t */
void squeeze(char s[], char t[]) {
    int j, k;
    for (int i = 0; t[i] != '\0'; i++) {
        for (j = k = 0; s[j] != '\0'; j++)
            if (s[j] != t[i])
                s[k++] = s[j];
        s[k] = '\0';
    }
}
