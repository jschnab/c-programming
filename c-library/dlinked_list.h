enum DLIST_TYPES {
    INT    = 1,
    FLOAT  = 2,
    STRING = 3,
};


typedef struct dlnode {
    void *val;
    char type;
    struct dlnode *next;
    struct dlnode *prev;
} DListNode;


void dlist_append(DListNode *, void *, char);
