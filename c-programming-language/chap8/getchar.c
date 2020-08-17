#include <unistd.h>


#define BUFSIZE 1024


/* unbuffered getchar */
int unbuf_getchar(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsighed char) c : EOF;
}


/* buffered getchar */
int buf_getchar(void) {
    static char buf[BUFSIZE];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {  /* buffer is empty */
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }

    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
