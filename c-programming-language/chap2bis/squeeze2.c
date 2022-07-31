#include <stdio.h>

void squeeze(char *, char *);

int main(){
    char s1[] = "hello";
    char s2[] = "world";
    squeeze(s1, s2);
    printf("s1 = %s\n", s1);
}

void squeeze(char *a, char *b) {
    int i, j, k;
    for (j = 0; b[j] != '\0'; j++) {
        for (i = 0, k = 0; a[i] != '\0'; i++) {
            if (a[i] != b[j]) {
                a[k++] = a[i];
            }
        }
        a[k] = '\0';
    }
}
