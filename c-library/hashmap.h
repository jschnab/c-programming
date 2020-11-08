#ifndef HASH_MAP_H
#define HASH_MAP_H


typedef struct hm_item {
    char *key;
    void *value;
    char type;
} HMItem;


typedef struct hashmap {
    int base_size;
    int size;
    int count;
    HMItem **items;
} HashMap;


void *hm_copy_value(void *, char);
HMItem *hm_create_item(char *, void *, char);
void hm_delete(HashMap *, char *);
void hm_delete_hashmap(HashMap *);
void hm_delete_item(HMItem *);
int hm_get_hash(char *, int, int);
int hm_hash(char *, int, int);
HashMap *hm_init();
HashMap *hm_init_sized(int);
void hm_insert(HashMap *, char *, void *, char);
int hm_is_prime(int);
int hm_next_prime(int);
void hm_resize(HashMap *, int);
void hm_resize_down(HashMap *);
void hm_resize_up(HashMap *);
void *hm_search(HashMap *, char *);


#endif  /* HASH_TABLE_H */
