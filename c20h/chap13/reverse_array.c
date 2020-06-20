#include <stdio.h>


#define SIZE 10
#define N_ELEMS(x) (sizeof(x) / (sizeof((x)[0])));


static void enter(int t[], int n) {
    int i;
    for (i = 0; i < n; i ++) {
        printf("Item %d: ", i + 1);
        (void) scanf("%d%*c", &t[i]);
    }
}


static void display(int t[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("\n");
}


static void reverse(int t[], int n) {
    int i, j, tmp;
    for (i = 0, j = n - 1; i < j; i++, j--) {
        tmp = t[i];
        t[i] = t[j];
        t[j] = tmp;
    }
}


int main() {
    int arr[SIZE];
    enter(arr, SIZE);
    int n = (int) N_ELEMS(arr);
    printf("Initial array:\n");
    display(arr, n);
    reverse(arr, n);
    printf("Reversed array:\n");
    display(arr, n);
    return 0;
}
