#include <stdio.h>
#include <stdlib.h>


void filecopy(FILE *, FILE *);


int main(int argc, char *argv[]) {
    FILE *fp;
    char *prog = argv[0];

    if (argc == 1)  /* no args, copy standard input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}


void filecopy(FILE *input, FILE *output) {
    int c;
    while ((c = getc(input)) != EOF)
        putc(c, output);
}
