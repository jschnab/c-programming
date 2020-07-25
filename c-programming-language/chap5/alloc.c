#include <stdio.h>


#define ALLOCSIZE 10000  /* size of available space */


static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;  /* next free position, equivalent to
                                    static char *allocp = &allocbuf[0]; */


/* return pointer to n characters */
char *alloc(int n) {
    /* it fits */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;  /* old p */
    }

    /* not enough room */
    else
        return 0;  /* zero is never a valid address for data */
}


/* free storage pointed to by p */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
