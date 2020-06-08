#include <stdio.h>


#define LINELENGTH 100


int main() {
    char line[LINELENGTH];
    FILE * p_file;
    p_file = fopen("essay.txt", "r");
    while (!feof(p_file)) {
        fgets(line, LINELENGTH, p_file);
        // fgets will fail before feof() returns True
        // so we would print twice the last line without the
        // following if statement
        if (!feof(p_file))
            printf("%s", line);
    }
    fclose(p_file);
    return 0;
}
