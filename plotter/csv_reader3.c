#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// node linked list containing double data
typedef struct node {
    double data;
    struct node *next;
} Node;

// node of linked list containing other linked lists
typedef struct node_l {
    Node *data;
    struct node_l *next;
} Node_l;

// array of 'double' numbers and variable to store array size
typedef struct arr {
    double *values;
    size_t length;
} sized_arr;


// function declarations to work with "double" linked lists
void insert_begin(double x, Node **head);
void insert_end(double x, Node **head);
void traverse(Node *head);
int get_size(Node *head);
void delete_begin(Node **head);
void delete_end(Node **head);

// function declarations to work with linked lists containing
// other linked lists
void insert_begin_l(Node *data, Node_l **head);
void insert_end_l(Node *data, Node_l **head);
void traverse_l(Node_l *head);
int get_size_l(Node_l *head);
void delete_begin_l(Node_l **head);
void delete_end_l(Node_l **head);

// function to convert a linked list to an array of double
sized_arr convert_list_array(Node *list);

// statistical functions
void swap(double *array, int first, int second);
int partition(double *array, int p, int r);
void quicksort(double *array, int p, int r);
double median(sized_arr array);

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("Please provide a filename : ./csv_reader3 <file name>\n");
        exit(0);
    }

    else if (argc > 2) {
        printf("Please provide a single argument.\n");
        exit(0);
    }

    // open file
    FILE *csv = NULL;
    csv = fopen(argv[1], "r");
    if (csv == NULL) {
        printf("Could not read file\n");
        exit(0);
    }
    
    char line[100] = {0};

    char *token;

    // this is a linked list made of linked lists
    Node_l *dataframe = NULL;

    // iterate through file rows
    // put row in a linked list
    printf("Reading CSV file '%s'\n", argv[1]);
    while (fgets(line, 100, csv) != NULL) {
        Node *row = NULL;

        // iterate through characters
        // put character in linked list
        token = strtok(line, ",");

        while (token != NULL) {
            insert_end(atof(token), &row);
            token = strtok(NULL, ",");
        }

        insert_end_l(row, &dataframe);
    }

    printf("Finished reading file\n\n");

    traverse_l(dataframe);

    fclose(csv);

    Node *temp = dataframe->data;
    printf("\nTraverse temp:\n");
    traverse(temp);
    printf("\n");

    sized_arr array = convert_list_array(dataframe->next->data);

    quicksort(array.values, 0, array.length - 1);

    printf("Sorted array\n");

    int i = 0;
    for (i = 0; i < array.length; i++)
        printf("array[%d] = %f\n", i, array.values[i]);

    printf("\nMedian : %f\n", median(array));

    return 0;
}

sized_arr convert_list_array(Node *list) {
    sized_arr sized_array;
    int size_list = get_size(list);
    double *array = NULL;
    array = malloc(sizeof(double) * size_list);
    Node *temp = list;
    int i;
    for (i = 0; i < size_list; i++) {
        array[i] = temp->data;
        temp = temp->next;
    }
    sized_array.values = array;
    sized_array.length = size_list;
    return sized_array;
}

// functions to work with linked lists containing double data
void insert_begin(double x, Node **head) {
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

void insert_end(double x, Node **head) {
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
void insert_begin_l(Node *data, Node_l **head) {
    Node_l *n;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (*head == NULL) {
        n->data = data;
        n->next = NULL;
        *head = n;
        return;
    }
    n->data = data;
    n->next = *head;
    *head = n;
}

void insert_end_l(Node *data, Node_l **head) {
    Node_l *n, *temp;
    n = (Node_l*) malloc(sizeof(Node_l));
    if (*head == NULL) {
        n->data = data;
        n->next = NULL;
        *head = n;
        return;
    }
    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = n;
    n->data = data;
    n->next = NULL;
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

void delete_begin_l(Node_l **head) {
    Node_l *n;
    if ((*head) == NULL) {
        printf("Linked list is already empty.\n");
        return;
    }
    n = (*head)->next;
    free(*head);
    *head = n;
}

void delete_end_l(Node_l **head) {
    Node_l *n, *m;
    if (*head == NULL) {
        printf("Linked list is already empty.\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        head = NULL;
        return;
    }
    n = *head;
    while (n->next != NULL) {
        m = n;
        n = n->next;
    }
    m->next = NULL;
    free(n);
}

void swap(double *array, int first, int second) {
    double temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

int partition(double *array, int p, int r) {
    int q = p;
    int j;
    for (j = p; j < r; j++) {
        if (array[j] <= array[r]) {
            swap(array, q, j);
            q++;
        }
    }
    swap(array, q, r);
    return q;
}

void quicksort(double *array, int p, int r) {
    if (p < r) {
        int q = partition(array, p, r);
        quicksort(array, p, q - 1);
        quicksort(array, q + 1, r);
    }
}

double median(sized_arr array) {
    double median;
    if (array.length & 1) {
        int med_index;
        med_index = (array.length - 1) / 2;
        median = array.values[med_index];
    }
    else {
        float med_index;
        int index_a, index_b;
        med_index = (float) (array.length - 1) / 2;
        index_a = floor(med_index);
        index_b = ceil(med_index);
        median = (array.values[index_a] + array.values[index_b]) / 2;
    }
    return median;
}

