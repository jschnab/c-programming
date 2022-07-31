#include <stdio.h>

int reverse(char *s, int i) {
    if (*(s + i) != '\0') {
        int j = reverse(s, i + 1);
        if (i > j) {
            char tmp = *(s + i);
            *(s + i) = *(s + j);
            *(s + j) = tmp;
        }
        return j + 1;
    }
    return 0;
}

int main() {
    char s[] = "bonjour";
    reverse(s, 0);
    printf("s = %s\n", s);
    return 0;
}
