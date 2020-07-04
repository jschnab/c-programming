/* this program uses external variables instead of functions arguments
 * for pedagogic purposes, it would be more readable and maintainable
 * to have functions with arguments */

#include <stdio.h>

#define MAXLINE 1000  /* maximum input line size */

int max;  /* maximum length seen so far */
char line[MAXLINE];  /* current input line */
char longest[MAXLINE];  /* longest line saved here */

int get_line(void);
void copy(void);


/* print the longest input line */
int main() {
    int len = 0;  /* current line length */

    max = 0;
    while ((len = get_line()) > 0)
        if (len > max) {
            max = len;
            copy();
        }

    if (max > 0)  /* there was a line */
        printf("%s", longest);

    return 0;
}


/* read a line into s, return length */
int get_line(void) {
    int c, i;

    for (
        i = 0;
        i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n';
        ++i
    )
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}


/* copy 'from' into 'to', assume 'to' is large enough */
void copy(void) {
    int i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
