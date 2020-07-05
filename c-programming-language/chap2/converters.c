#include <stdio.h>
#include <ctype.h>


int atoi(char s[]);
int ctoi(char c);
int htoi(char s[]);
int lower(char c);


int main() {
    printf("0x1F = %d\n", htoi("0x1F"));
    printf("0xABCD69 = %d\n", htoi("0xABCD69"));

    char string[] = "HeLlO wOrLd";
    printf("original: %s\n", string);
    for (int i = 0; string[i] != '\0'; ++i)
        string[i] = lower(string[i]);
    printf("lowered: %s\n", string);
    return 0;
}


/* convert a string representing a number to the corresponding integer */
int atoi(char s[]) {
    int answer;
    for (int i = 0; isdigit(s[i]); ++i)
        answer = 10 * answer + (s[i] - '0');
    return answer;
}


/* convert a character representing an integer to the corresponding integer */
int ctoi(char c) {
    return c - '0';
}


/* convert a string representing a hexadecimal number to an integer */
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


/* convert a character to lower caser */
int lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    return c;
}
