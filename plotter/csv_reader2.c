// read and parse a csv file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // open file
    FILE *file = NULL;
    char line[100] = {0};
    char *tokens;
    int i = 0;

    file = fopen("test.csv", "r");

    if (file == NULL) {
        printf("Could not read file.\n");
        exit(0);
    }

    else {
        while (fgets(line, 100, file) != NULL) {
            printf("line %d : %s\n", i, line);
            i++;
            
            // break the line into single values
            tokens = strtok(line, ",");
            while (tokens != NULL) {
                printf("token : %s\n", tokens);
                tokens = strtok(NULL, ",");
            }
        }
    }
    
    fclose(file);

    return 0;
}
