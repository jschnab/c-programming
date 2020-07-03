#include <stdio.h>


int main() {
    int c;
    int flag = 0;
    while (1) {
        c = getchar();
        if (c != EOF) {
            if (c == ' ') {
                if (!flag) {
                    flag = 1;
                    putchar(c);
                }
            }
            else {
                flag = 0;
                putchar(c);
            }
        }
        else break;
    }
    return 0;
}
