#include <stdio.h>
#include <stdlib.h>

// node linked list containing float data
typedef struct node {
    float data;
    struct node *next;
} Node;

// node of linked list containing other linked lists
typedef struct node_l {
    Node *data;
    struct node_l *next;
} Node_l;


// function declarations to work with "float" linked lists
void insert_begin(float x, Node **head);
void insert_end(float x, Node **head);
void traverse(Node *head);
int get_size(Node *head);
void delete_begin(Node **head);
void delete_end(Node **head);

// function declarations to work with linked lists containing
// other linked lists
Node_l * insert_begin_l(Node *data, Node_l *head);
Node_l * insert_end_l(Node *data, Node_l *head);
void traverse_l(Node_l *head);
int get_size_l(Node_l *head);
Node_l * delete_begin_l(Node_l *head);
Node_l * delete_end_l(Node_l *head);


int main(int argc, char *argv[]) {

    // create linked list 1
    Node *mylist1 = NULL;

    int i = 1;
    for (i = 1; i < 5; i++) {
        insert_end((float)i, &mylist1);
    }
    printf("Adding 3.14 at the beginning of mylist1\n");
    insert_begin(3.14, &mylist1);

    // traverse linked list 1
    printf("Items of mylist1 : ");
    traverse(mylist1);

    printf("Removing first element of mylist1\n");
    delete_begin(&mylist1);
    printf("Items of mylist1 : ");
    traverse(mylist1);

    printf("Removing last element of mylist1\n");
    delete_end(&mylist1);
    printf("Items of mylist1 : ");
    traverse(mylist1);

    printf("Size of mylist1: %d\n", get_size(mylist1));

    // create linked list 2
    Node *mylist2 = NULL;
    for (i = 5; i < 10; i++) {
        insert_end((float)i, &mylist2);
    }

    // create linked list containing mylist1 and mylist2
    Node_l *superlist = NULL;
    superlist = insert_end_l(mylist1, superlist);
    superlist = insert_end_l(mylist2, superlist);

    printf("Size of superlist : %d\n", get_size_l(superlist));

    traverse_l(superlist);

    return 0;
}


// functions to work with linked lists containing float data
void insert_begin(float x, Node **head) {
    Node *n;
    n = (Node*) malloc(sizeof(Node));
    if (*head == NULL) {
        n->data = x;
        n->next = NULL;
        *head = n;
        return;
    }
    n->data = x;
    n->next = *head;
    *head = n;
}

void insert_end(float x, Node **head) {
    Node *n, *temp;
    n = (Node*) malloc(sizeof(Node));
    if (*head == NULL) {
        n->data = x;
        n->next = NULL;
        *head = n;
        return;
    }
    temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->data = x;
    n->next = NULL;
}

void traverse(Node *head) {
    Node *n;
    n = head;
    if (n == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    while (n->next != NULL) {
        printf("%.3f, ", n->data);
        n = n->next;
    }
    printf("%.3f\n", n->data);
}

int get_size(Node *head) {
    Node *n;
    n = head;
    if (n == NULL)
        return 0;
    int c = 1;
    while (n->next != NULL) {
        c++;
        n = n->next;
    }
    return c;
}

void delete_begin(Node **head) {
    Node *n;
    if (*head == NULL) {
        printf("Linked list is already empty.\n");
    }
    n = (*head)->next;
    free(*head);
    *head = n;
}

void delete_end(Node **head) {
    Node *n, *m;
    if (*head == NULL) {
        printf("Linked list is already empty.\n");
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    n = *head;
    while (n->next != NULL) {
        m = n;
        n = n->next;
    }
    m->next = NULL;
    free(n);
}

// functions to work with linked lists containing
// other linked lists
Node_l * insert_begin_l(Node *data, Node_l *head) {
    Node_l *n;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (head == NULL) {
        head = n;
        head->data = data;
        head->next = NULL;
        return head;
    }
    n->data = data;
    n->next = head;
    head = n;
    return head;
}

Node_l * insert_end_l(Node *data, Node_l *head) {
    Node_l *n, *temp;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (head == NULL) {
        head = n;
        head->data = data;
        head->next = NULL;
        return head;
    }
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->data = data;
    n->next = NULL;
    return head;
}

void traverse_l(Node_l *head) {
    Node_l *n;
    n = head;
    if (n == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    int i = 1;
    while (n->next != NULL) {
        printf("Row %d : ", i);
        traverse(n->data);
        n = n->next;
        i++;
    }
    printf("Row %d : ", i);
    traverse(n->data);
}

int get_size_l(Node_l *head) {
    Node_l *n;
    n = head;
    if (n == NULL)
        return 0;
    int c = 1;
    while (n->next != NULL) {
        c++;
        n = n->next;
    }
    return c;
}

Node_l * delete_begin_l(Node_l *head) {
    Node_l *n;
    if (head == NULL) {
        printf("Linked list is already empty.\n");
        return head;
    }
    n = head->next;
    free(head);
    head = n;
    return head;
}

Node_l * delete_end_l(Node_l *head) {
    Node_l *n, *m;
    if (head == NULL) {
        printf("Linked list is already empty.\n");
        return head;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return head;
    }
    n = head;
    while (n->next != NULL) {
        m = n;
        n = n->next;
    }
    m->next = NULL;
    free(n);
    return head;
}
