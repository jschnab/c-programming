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


typedef struct dlist {
    DListNode *head;
    DListNode *tail;
    int n;
} DList;


DList *dlist_init();
void dlist_append(DList *, void *, char);
