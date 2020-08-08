#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAXWORD 100


struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};


struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *str_dup(char *);


/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);

    return 0;
}


/* add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {  /* a new node has arrived */
        p = talloc();  /* make a new node */
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;  /* repeated word */
    else if (cond < 0)  /* less than into left subtree */
        p->left = addtree(p->left, w);
    else  /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}


/* print the tree in lexicographical order (in-order traversal) */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s %d\n", p->word, p->count);
        treeprint(p->right);
    }
}


/* make a node */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}


/* make a duplicate of a string */
char *str_dup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  /* account for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
