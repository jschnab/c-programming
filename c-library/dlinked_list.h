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


void dlist_append(DList *, void *, char);
int dlist_compare_nodes(DListNode *, DListNode *);
DList *dlist_copy(DList *);
DListNode *dlist_copy_node(DListNode *);
DListNode *dlist_create_node(void *, char);
void dlist_delete(DList *, int);
char dlist_equal(DList *, DList *);
DList *dlist_from_array(void *, char, int);
DListNode *dlist_get_node(DList *, int);
char dlist_get_type(DList *, int);
void *dlist_get_value(DList *, int);
DList *dlist_init();
void dlist_insert(DList **, void *, char, int);
int dlist_length(DList *);
void dlist_print(DList *);
DList *dlist_slice(DList *, int, int);
void dlist_sort(DList *);
void dlist_sort_helper(DList *, int, int);
void dlist_swap_nodes(DListNode *, DListNode *);
void dlist_to_array(DList *, void *, char);
void dlist_to_strarray(DList *, char *array[]);
