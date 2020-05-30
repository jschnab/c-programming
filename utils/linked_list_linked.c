// this file defines functions to work with linked lists
// storing data of type "Node" (linked list storing float)

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct node {
    float data;
    struct node *next;
} Node;

typedef struct node_l {
    Node *data;
    struct node_l *next;
} Node_l;


Node_l * insert_begin_l(Node *data, Node_l *head) {
    Node_l *n;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (head == NULL) {
        head = n;
        head->data = *data;
        head->next = NULL;
        return head;
    }
    n->data = *data;
    n->next = head;
    head = n;
    return head;
}

Node_l * insert_end_l(Node *data, Node_l *head) {
    Node_l *n, *temp;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (head == NULL) {
        head = n;
        head->data = *data;
        head->next = NULL;
        return head;
    }
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->data = *data;
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
        printf("Item %d : ", i);
        traverse(n->data);
        n = n->next;
        i++;
    }
    printf("Last item : ");
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
