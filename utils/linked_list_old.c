#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node *next;
} Node;

Node *start = NULL;
void insert_begin(float);
void insert_end(float);
void traverse();
void delete_begin();
void delete_end();
int count = 0;

int main(int argc, char *argv[]) {
    int input;
    float data;
    char sig_quit = 0;

    while (!sig_quit) {
        printf("1. Insert element at beginning\n");
        printf("2. Insert element at end of linked list\n");
        printf("3. Traverse linked list\n");
        printf("4. Delete element from beginning\n");
        printf("5. Delete element from end\n");
        printf("6. Exit\n");

        scanf("%d%*c", &input);

        switch (input) {
            case 1: printf("Enter value of element\n");
                    scanf("%f%*c", &data);
                    insert_begin(data);
                    break;

            case 2: printf("Enter value of element\n");
                    scanf("%f%*c", &data);
                    insert_end(data); 
                    break;

            case 3: traverse();
                    break;

            case 4: delete_begin();
                    break;

            case 5: delete_end();
                    break;

            case 6: sig_quit = 1;
                    break;

            default: printf("Please enter a valid value\n");
                     break;
        }
    }
    return 0;
}

void insert_begin(float x) {
    Node *n;
    n = (Node*) malloc(sizeof(Node));
    count++;
    if (start == NULL) {
        start = n;
        start->data = x;
        start->next = NULL;
        return;
    }
    n->data = x;
    n->next = start;
    start = n;
}

void insert_end(float x) {
    Node *n, *temp;
    n = (Node*) malloc(sizeof(Node));
    count++;
    if (start == NULL) {
        start = n;
        start->data = x;
        start->next = NULL;
        return;
    }
    temp = start;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->data = x;
    n->next = NULL;
}

void traverse() {
    Node *n;
    n = start;
    if (n == NULL) {
        printf("linked list is empty.\n");
        return;
    }
    printf("There are %d elements in the list.\n", count);
    while (n->next != NULL) {
        printf("%f\n", n->data);
        n = n->next;
    }
    printf("%f\n", n->data);
}

void delete_begin() {
    Node *n;
    float d;
    if (start == NULL) {
        printf("Linked list is already empty.\n");
        return;
    }
    d = start->data;
    n = start->next;
    free(start);
    start = n;
    count--;
    printf("%f deleted from beginning successfully.\n", d);
}

void delete_end() {
    Node *n, *m;
    float d;
    if (start == NULL) {
        printf("Linked list is already empty.\n");
        return;
    }
    count --;
    if (start->next == NULL) {
        d = start->data;
        free(start);
        start = NULL;
        printf("%f deleted from start successfuly.\n", d);
        return;
    }
    n = start;
    while (n->next != NULL) {
        m = n;
        n = n->next;
    }
    d = n->data;
    m->next = NULL;
    free(n);
    printf("%f deleted from end successfully.\n", d);
}
