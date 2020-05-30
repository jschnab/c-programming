#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char name[40] = {0};
    FILE *file = NULL;

    file = fopen("test.txt", "a");

    if (file == NULL) {
        printf("Error when opening file.");
        return 1;
    }

    printf("Please enter your name : ");
    scanf("%s%*c", name);

    fprintf(file, "Bonjour %s!\n", name);
    
    fclose(file);

    return 0;
}
