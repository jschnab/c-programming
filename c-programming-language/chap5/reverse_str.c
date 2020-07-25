#include <stdio.h>


int main() {
    char s[] = "hello world";
    int i = 0, j = 0;
    char tmp;

    while (s[j] != '\0')
        j++;

    j--;

    while (i < j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }

    printf("%s\n", s);

    return 0;
}
