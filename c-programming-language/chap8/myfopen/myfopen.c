#include <fcntl.h>
#include <unistd.h>
#include "mystdio.h"


#define PERMS    0666  /* RW for owner, group, others */


/* fopen: open file, return file ptf */
FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag &(_READ | _WRITE)) == 0)
            break;  /* found free slot */
    if (fp >= _iob + OPEN_MAX)  /* no free slot */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)  /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}


FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};


int main() {
    FILE *fp;
    int c;

    if ((fp = fopen("hello.txt", "r")) == NULL) {
        return 1;
    } else {
        while ((c = getc(fp)) != EOF)
            putc(c, stdout);
    }

    return 0;
}
