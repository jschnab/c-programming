#include <stdio.h>

#include "atof.c"
#include "getline.c"


#define MAXLINE 100


int main() {
    double sum;
    char line[MAXLINE];
    sum = 0;
    while (get_line(line, MAXLINE) > 0) {
        printf("%f\n", sum += atof(line));
    }
    return 0 ;
}
