#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMS 0666


void error(char *, ...);
void filecopy(int, int);


int main(int argc, char *argv[]) {
    char *fname;
    int fd;
    if (argc == 1) {
        filecopy(0, 1);
    }
    else {
        while (--argc > 0) {
            fname = *++argv;
            if ((fd = open(fname, O_RDONLY, 0)) == -1) {
                error("can't open %s", fname);
            }
            filecopy(fd, 1);
        }
    }
}


void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}


void filecopy(int input, int output) {
    char buf[BUFSIZ];
    int n;
    while ((n = read(input, buf, BUFSIZ)) > 0) {
        if (write(output, buf, n) != n) {
            error("error writing on stdout");
        }
    }
}
