#include <stdio.h>


int main() {
    char *s = "pack my box, will you?";

    /* array counting printable characters starting at 'space' */
    char count[95] = {0};

    /* iterate through string and increment 'count' array */
    int i = 0;
    while (*(s+i) != '\0')
        count[*(s + i++)-32]++;

    /* check if any character has count > 1 */
    for (i = 0; i <= 95; i++)
        if (count[i] > 1)
            printf("character '%c' is duplicated\n", i + 32);

    return 0;
}
