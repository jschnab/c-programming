#include <stdio.h>


int main() {
    int i = 1;
    int j = 11;

    void func() {
        int i = 5;
        i++;  // the local variable is incremented
        j++;  // the variable from the enclosing scope is incremented
    }

    printf("i = %d, j = %d\n", i, j);
    func();
    printf("i = %d, j = %d\n", i, j);

    return 0;
}
