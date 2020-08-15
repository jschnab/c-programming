#include <stdio.h>


typedef struct tnode *Treeptr;
typedef struct tnode {
    char *word;
    int count;
    Treeptr left;
    Treeptr right;
} Treenode;


Treeptr talloc(void) {
    return (Treeptr) malloc(sizeof(Treenode));
}
