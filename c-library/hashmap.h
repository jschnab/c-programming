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
HMItem *hm_create_item(void *, void *, char, char);
