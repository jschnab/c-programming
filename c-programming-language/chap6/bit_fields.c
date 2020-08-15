#include <stdio.h>


/* manual way to use bit fields */
#define KEYWORD 01
#define EXTERNAL 02
#define STATIC 04

/* or
 * enum {
 *     KEYWORD = 01,
 *     EXTERNAL = 02,
 *     STATIC = 04
 * };
 */


/* better way to use bit fields
 * flags contains three 1-bit fields
 */
struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
} flags;


int main(int argc, char *argv[]) {
    /* using manual bit fields
    char flags = 0;
    printf("initialized: flags = %d\n", flags);
    flags |= EXTERNAL | STATIC;
    printf("setting EXTERNAL and STATIC: flags = %d\n", flags);
    flags &= ~(EXTERNAL | STATIC);
    printf("resetting EXTERNAL and STATIC: flags = %d\n", flags);
    */

    flags.is_extern = flags.is_static = 1;
    flags.is_extern = flags.is_static = 0;
    if (flags.is_extern == 0 && flags.is_static == 0)
        printf("EXTERNAL and STATIC are both False\n");

    return 0;
}
