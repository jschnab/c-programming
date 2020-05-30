#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    // number of friends
    int n = 0;
    int i = 0;

    printf("How many friends do you have ? ");
    scanf("%d%*c", &n);

    // pointer to array to store age of friends
    int *amis = malloc(n * sizeof(int));
    if (amis == NULL) {
        printf("Memory allocation problem.");
        exit(0);
    }

    // iterate to store age of friends
    for (i = 0; i < n; i++) {
        printf("Age of friend %d : ", i + 1);
        scanf("%d%*c", amis + i);
    }

    // print age of friends
    printf("\n\nYour friends have the following ages\n");
    for (i = 0; i < n; i++) {
        printf("Age of friend %d : %d\n", i + 1, *(amis + i));
    }

    free(amis);

    return 0;
}
