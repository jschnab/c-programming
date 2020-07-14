#include <stdio.h>


int binary_search(int x, int v[], int n);


int main() {
    int x = 0;
    int v[] = {0, 1, 2, 3};
    printf("%d is in v at position %d\n", x, binary_search(x, v, 5));
    return 0;
}


int binary_search(int x, int v[], int n) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low < high) {
        mid = (low + high) / 2;  /* floor of (low + high) / 2 */
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }

    if (v[low] == x)
        return low;

    return -1;
}
