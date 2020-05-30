// this file defines functions to work with linked lists
// storing data of type float

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node *next;
} Node;

Node* insert_begin(float x, Node *head) {
    Node *n;
    n = (Node*) malloc(sizeof(Node));
    if (head == NULL) {
        head = n;
        head->data = x;
        head->next = NULL;
        return head;
    }
    n->data = x;
    n->next = head;
    head = n;
    return head;
}

Node* insert_end(float x, Node *head) {
    Node *n, *temp;
    n = (Node*) malloc(sizeof(Node));
    if (head == NULL) {
        head = n;
        head->data = x;
        head->next = NULL;
        return head;
    }
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->data = x;
    n->next = NULL;
    return head;
}

void traverse(Node *head) {
    Node *n;
    n = head;
    if (n == NULL) {
        printf("linked list is empty.\n");
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

Node* delete_begin(Node *head) {
    Node *n;
    if (head == NULL) {
        printf("Linked list is already empty.\n");
        return head;
    }
    n = head->next;
    free(head);
    head = n;
    return head;
}

Node* delete_end(Node *head) {
    Node *n, *m;
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
