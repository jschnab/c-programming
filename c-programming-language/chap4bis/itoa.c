#include <stdio.h>

void itoa(int n, char *s) {
    char tmp;
    int i = 0, j;
    while (n > 0) {
        s[i++] = n % 10 + '0';
        n /= 10;
    }
    s[i] = '\0';
    j = i - 1;
    i = 0;
    while (i < j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++, j--;
    }
}

int helper(int n, char *s) {
    if (n > 0) {
        int i = helper(n / 10, s);
        s[i] = n % 10 + '0';
        return i + 1;
    }
    return 0;
}

void itoa_recur(int n, char *s) {
    int end = helper(n, s);
    s[end] = '\0';
}

int main() {
    char s[10];
    itoa_recur(1234567890, s);
    printf("s = %s\n", s);
    return 0;
}
