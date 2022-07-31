#include <stdio.h>

void swap(int *v, int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void qsort(int *v, int left, int right) {
    int i, last;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int main() {
    int a[] = {5, 4, 3, 2, 1};
    qsort(a, 0, 5);
    for (int i = 0; i < 5; ++i)
        printf((i < 4) ? "%d " : "%d\n", a[i]);
    return 0;
}
