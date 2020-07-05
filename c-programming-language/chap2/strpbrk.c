#include <stdio.h>


int strpbrk(char s[], char t[]);


int main() {
    char string1[] = "hello";
    char string2[] = "world";
    printf(
        "strpbrk(\"%s\", \"%s\") = %d\n",
        string1,
        string2,
        strpbrk(string1, string2)
    );
    return 0;
}


/* return first location in string s where any character from string t
 * occurs, or -1 if s contains no character from t */
int strpbrk(char s[], char t[]) {
    for (int i = 0; s[i] != '\0'; ++i)
        for (int j = 0; t[j] != '\0'; ++j)
            if (s[i] == t[j])
                return i;
    return -1;
}
