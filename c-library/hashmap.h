typedef struct hm_item {
    void *key;
    void *value;
} HMItem;


typedef struct hashmap {
    int size;
    int count;
    HMItem **items;
} HashMap;


HashMap *hm_init();
void *hm_copy_value(void *, char);
HMItem *hm_create_item(char *, void *, char);
void hm_delete_hashmap(HashMap *);
void hm_delete_item(HMItem *);
void hm_hash(char *, int, int);
