#include <stdio.h>
#include <ctype.h>

/* atof: convert string s to double */
double atof(char s[]) {
    double val, power, exponent = 1.0;
    int i, sign, x;
    for (i = 0; isspace(s[i]); ++i)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') ++i;
    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') ++i;
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (tolower(s[i++]) == 'e') {
        if (s[i] == '-') {
            ++i;
            for (x = 0; isdigit(s[i]); ++i) {
                x = 10 * x + (s[i] - '0');
            }
            while (x-- > 0) {
                exponent /= 10;
            }
        }
        else {
            for (x = 0; isdigit(s[i]); ++i) {
                x = 10 * x + (s[i] - '0');
            }
            while (x-- > 0) {
                exponent *= 10;
            }
        }
    }
    return sign * val * exponent / power;
}
