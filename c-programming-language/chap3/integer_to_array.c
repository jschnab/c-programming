#include <stdio.h>
#include <string.h>


void reverse(char s[]);
void itoa(int n, char s[]);


int main() {
    int number = -45;
    char str[10];
    itoa(number, str);
    printf("%s\n", str);
    return 0;
}


void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;

    i = 0;
    do {  /* generate digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);  /* delete it */


    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s);
}
