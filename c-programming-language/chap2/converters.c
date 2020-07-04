#include <stdio.h>
#include <ctype.h>


int atoi(char s[]);
int htoi(char s[]);


int main() {
    printf("0x1F = %d\n", htoi("0x1F"));
    printf("0xABCD69 = %d\n", htoi("0xABCD69"));
    return 0;
}


int ctoi(char c) {
    return c - '0';
}


int htoi(char s[]) {
    int answer = 0;
    for (
        int i = 2;
        isdigit(s[i]) || (s[i] >= 'A' && s[i] <= 'F');
        ++i
    ) {
        if (isdigit(s[i]))
            answer = 16 * answer + ctoi(s[i]);
        else
            answer = 16 * answer + (s[i] - 'A' + 10);
    }
    return answer;
}
