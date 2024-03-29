#include <unistd.h>

#define BUFSIZ 1024


int getchar_buf(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }

    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}


int getchar_buf(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
