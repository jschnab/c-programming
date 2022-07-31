#include <stdio.h>
#include <string.h>

int strrindex(char *, char *);

int main() {
    printf("%d\n", strrindex("banana split", "na"));
    printf("%d\n", strrindex("na", "banana split"));
    return 0;
}

int strrindex(char *s, char *t) {
    int index = -1;
    int i = 0;
    while (i < strlen(s)) {
        int j = 0;
        while (j < strlen(t) && s[i++] == t[j++]);
        if (j == strlen(t)) {
            index = i - j;
        }
    }
    return index;
}

/*
   0123456789
   banana split

   01
   na

   i 6
   j 2

*/
