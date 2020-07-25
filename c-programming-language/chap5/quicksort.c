#include <stdio.h>


void quicksort(int *, int, int);
void swap(int *, int, int);


int main() {
    int array[6] = {12, 7, 14, 9, 10, 11};
    int i;
    for (i=0; i < 6; i++)
        printf("%d ", array[i]);
    printf("\n");
    quicksort_bug(array, 0, 5);
    for (i=0; i < 6; i++)
        printf("%d ", array[i]);
    printf("\n");
    return 0;
}


void quicksort(int *array, int left, int right) {
    if (left >= right)
        return;

    int i, pivot;
    pivot = left;

    for (i = left; i < right; i++) {
        if (array[i] < array[right]) {
            swap(array, i, pivot);
            pivot++;
        }
    }

    swap(array, pivot, right);
    quicksort(array, left, pivot-1);
    quicksort(array, pivot+1, right);
}


void swap(int *array, int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}
