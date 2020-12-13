#ifndef HASH_SET_H
#define HASH_SET_H


typedef struct hashset {
    int base_size;
    int size;
    int count;
    char **items;
} HashSet;


void hs_add(HashSet *, char *);
void hs_discard(HashSet *, char *);
void hs_delete_set(HashSet *);
int hs_get_hash(char *, int, int);
int hs_hash(char *, int, int);
HashSet *hs_init();
HashSet *hs_init_sized(int);
int hs_is_prime(int);
int hs_next_prime(int);
void hs_resize(HashSet *, int);
void hs_resize_down(HashSet *);
void hs_resize_up(HashSet *);
int hs_search(HashSet *, char *);


#endif  /* HASH_SET_H */
