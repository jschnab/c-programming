// read and parse a csv file

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file = NULL;
    int c;
    int i = 0;

    // open file
    file = fopen("test.csv", "r");

    if (file == NULL) {
        printf("Could not read file.\n");
        exit(0);
    }

    // iterate over file data and print them
    // comma is 44
    // new line is 10
    else {
        while ((c = fgetc(file)) != EOF) {
            if (c == 10)
                printf("character %d : \\n\n", i);
            else
                printf("character %d : %c\n", i, c);
            i++;
        }
    }

    fclose(file);

    return 0;
}
