#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 101


struct nlist {  /* table entry */
    struct nlist *next;  /* next entry in the chain */
    char *name;  /* defined name */
    char *defn;  /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];  /* pointer table */


unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);


int main(int argc, char *argv[]) {
    install("bonjour", "hello");
    install("aurevoir", "goodbye");
    struct nlist *found;
    if ((found = lookup("bonjour")) != NULL)
        printf("%s = %s\n", found->name, found->defn);
    else
        printf("could not find name in table\n");
    return 0;
}


/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}


/* look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;  /* not found */
}


/* put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else  /* already there */
        free((void *) np->defn);  /* free previous defn */

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}
