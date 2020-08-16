typedef struct lnode {
    int val;
    struct lnode *next;  /* remember memory for this is not allocated */
} ListNode;


ListNode *list_append(ListNode *, int);
void list_delete(ListNode *, int);
char list_equal(ListNode *, ListNode *);
void list_insert(ListNode *, int, int);
void list_insert_front(ListNode **, int);
int list_length(ListNode *);
void list_print(ListNode *);
void list_reverse(ListNode **);
ListNode *list_copy(ListNode *);
ListNode *list_to_array(ListNode *, int *);
