#include <stdio.h>

#define N_ELEMS(x) (sizeof(x) / sizeof((x)[0]))


static int maxi(int arr[], size_t size);


int main() {
    int array1[] = {1, 10, 4, 5, -7};
    int array2[] = {2, 1, 14, 99};
    printf("Maximum of array 1 is %d\n", maxi(array1, N_ELEMS(array1)));
    printf("Maximum of array 2 is %d\n", maxi(array2, N_ELEMS(array2)));
    return 0;
}


static int maxi(int arr[], size_t size) {
    int i, max;
    for (i = 1, max = arr[0]; i < (int) size; i++) {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}
