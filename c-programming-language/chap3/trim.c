#include <stdio.h>
#include <string.h>


void trim_right(char s[]);


int main() {
    char s[] = "monsieur        \t\n";
    trim_right(s);
    printf("bonjour %s!\n", s);
    return 0;
}


/* remove trailing blanks, tabs, newlines */
void trim_right(char s[]) {
    int n;
    for (n = strlen(s)-1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
}
