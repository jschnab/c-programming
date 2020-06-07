#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    FILE * p_file;
    char file_name[20], first_name[20];
    int i, n;

    // create file and save data
    printf("Saving friend names in file...\n");
    printf("file name: ");
    (void) scanf("%s%*c", file_name);

    p_file = fopen(file_name, "w");
    if (p_file == NULL) {
        printf("error when creating file\n");
        exit(EXIT_FAILURE);
    }

    printf("number of entries: ");
    (void) scanf("%d%*c", &n);

    for (i = 0; i < n; i++) {
        printf("first name: ");
        (void) scanf("%s%*c", first_name);
        fprintf(p_file, "%s\n", first_name);
    }

    (void) fclose(p_file);

    // read file and print content
    printf("\nReading friend names from file...\n");
    p_file = fopen(file_name, "r");
    if (p_file == NULL) {
        printf("\aerror when opening file %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    while (!feof(p_file)) {
        (void) fscanf(p_file, "%s ", first_name);
        printf("name: %s\n", first_name);
    }

    (void) fclose(p_file);

    return 0;
}
