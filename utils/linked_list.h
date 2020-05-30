typedef struct node {
    float data;
    struct node *next;
} Node;

typedef struct node_l {
    Node data;
    struct node_l *next;
} Node_l;


Node insert_begin(float, Node);
Node insert_end(float, Node);
void traverse(Node);
int get_size(Node);
Node delete_begin(Node);
Node delete_end(Node);

Node_l * insert_begin_l(Node, Node_l);
Node_l insert_end_l(Node, Node_l);
void traverse_l(Node_l);
int get_size_l(Node_l);
Node_l delete_begin_l(Node_l);
Node_l delete_end_l(Node_l);
