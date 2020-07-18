#include <stdio.h>


#define square(x) (x) * (x)

#define swap(t,x,y) {t tmp = x; x = y; y = tmp;}


int main() {
    int i = 2;
    printf("i = %d\n", i);
    printf("square(i+1) = %d\n", square(i+1));


    float a = 2.0;
    float b = 3.14;
    swap(float, a, b);
    printf("a = %f\nb = %f\n", a, b);
    return 0;
}
