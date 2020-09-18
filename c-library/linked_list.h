enum LIST_TYPES {
    INT    = 1,
    FLOAT  = 2,
    STRING = 3,
};


typedef struct lnode {
    void *val;
    struct lnode *next;  /* remember memory for this is not allocated */
    char type;
} ListNode;


void list_append(ListNode *, void *, char);
ListNode *list_copy(ListNode *);
ListNode *list_create(void *, char);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
ListNode *list_from_args(int, char, ...);
void list_insert(ListNode *, void *, char, int);
void list_insert_front(ListNode **, void *, char);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
void list_to_array(ListNode *, void *, char);
void list_to_strarray(ListNode *head, char *array[]);
