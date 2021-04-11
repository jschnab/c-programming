#include <stdio.h>

int cube (int x);
void affiche (int tableau[], int tailleTableau);
int somme(int *tableau, int tailleTableau);

int main (int argc, char *argv[]) {
    int t = 4;
    int tab[t];
    int i;

    for (i = 0; i < 4; i++) {
        tab[i] = cube(i);
    }

    printf("adress of tab : %p\n\n", tab);

    affiche(tab, 4);

    printf("\nsum of values : %d\n", somme(tab, 4));

    return 0;
}

int cube (int x) {
    return x * x * x;
}

void affiche (int *tableau, int tailleTableau) {
    int i;
    printf("values of array : \n");
    for (i = 0; i < tailleTableau; i++) {
        printf("%d\n", tableau[i]);
    }
}

int somme(int tableau[], int tailleTableau) {
    int i;
    int s = 0;
    for (i = 0; i < tailleTableau; i++) {
        s += tableau[i];
    }
    return s;
}

