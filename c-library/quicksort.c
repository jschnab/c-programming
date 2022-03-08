#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int partition(int *A, int p, int r) {
    int tmp;
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            tmp = A[j];
            A[j] = A[i];
            A[i] = tmp;
        }
    }
    tmp = A[i+1];
    A[i+1] = A[r];
    A[r] = tmp;
    return i+1;
}


void quicksort(int *A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int len = 5;
    int A[len];
    for (int i = 0; i < len; i++) {
        A[i] = rand() % 100;
        printf("%d ", A[i]);
    }
    printf("\n");
    quicksort(A, 0, len-1);
    for (int i = 0; i < len; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
