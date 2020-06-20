#include <stdio.h>


void enter_array(int arr[], int n);
void display_array(int arr[], int n);
void insertion_sort(int arr[], int n);


int main() {
    int size;
    printf("Number of elements in the array: ");
    (void) scanf("%d%*c", &size);
    int array[size];
    enter_array(array, size);
    printf("Sorted array: ");
    insertion_sort(array, size);
    display_array(array, size);
    return 0;
}


void enter_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        (void) scanf("%d%*c", &arr[i]);
    }
}


void display_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void insertion_sort(int arr[], int n) {
    int i, current;
    for (i = 1; i < n; i++) {
        current = arr[i];
        while ((i > 0) && (current < arr[i - 1])) {
            arr[i] = arr[i - 1];
            i--;
        }
        arr[i] = current;
    }
}
