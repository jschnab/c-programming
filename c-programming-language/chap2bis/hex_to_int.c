#include <stdio.h>

int hex_to_int(char *);
int str_len(char *);
char to_lower(char);

int main() {
    printf("%d\n", hex_to_int("0XFAB"));
    return 0;
}

int hex_to_int(char *s) {
    int r = 0;
    char c ='\0';
    int e = 1;
    for (int i = str_len(s) - 1; i >= 0; --i) {
        if (to_lower(s[i]) == 'x')
            break;
        c = s[i];
        if (c >= 'A' && c <= 'F') {
            c = c - 'A' + 10;
        }
        else {
            c = c - '0';
        }
        r += e * c;
        e *= 16;
    }
    return r;
}

int str_len(char *s) {
    int i = 0;
    while (s[i] !='\0') ++i;
    return i;
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}
