typedef struct hm_item {
    void *key;
    void *value;
} HMItem;


typedef struct hashmap {
    int size;
    int count;
    HMItem **items;
} HashMap;
