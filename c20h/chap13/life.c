#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MATRIX_SIZE 24
#define SUB_MATRIX_SIZE (MATRIX_SIZE - 2)


// prototypes
static void initialize_matrix(int matrix[][MATRIX_SIZE]);
static void initialize_matrix_conway(int matrix[][MATRIX_SIZE]);
static int alive_neighbours(int matrix[][MATRIX_SIZE], int row, int col);
static void update_matrix(int matrix[][MATRIX_SIZE]);
static void display_matrix(int matrix[][MATRIX_SIZE]);
static void line_return(int width);


int main() {
    int i;
    int n_cycles;
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    char s[2];

    printf("Number of cycles: ");
    (void) scanf("%i%*c", &n_cycles);

    initialize_matrix_conway(matrix);
    printf("Initial population:\n");
    display_matrix(matrix);
    printf("Press a key to continue\n");
    (void) fgets(s, 2, stdin);

    for (i = 0; i < n_cycles; i++) {
        update_matrix(matrix);
        printf("Population after %d cycles:\n", i + 1);
        display_matrix(matrix);
        printf("Press a key to continue\n");
        (void) fgets(s, 2, stdin);
    }
    return 0;
}


// initialize starting matrix
static void initialize_matrix(int matrix[][MATRIX_SIZE]){
    int i, j, random;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            random = rand() % 100;
            if (random % 2 == 0)
                matrix[i][j] = 0;
            else
                matrix[i][j] = 1;
        }
    }
}


// initialize starting matrix in honor of John Conway
static void initialize_matrix_conway(int matrix[][MATRIX_SIZE]){
    int i, j;

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (
                (i == 10 && j == 9) || (i == 10 && j == 10) ||
                (i == 10 && j == 11) || (i == 11 && j == 9) ||
                (i == 11 && j == 11) || (i == 12 && j == 9) ||
                (i == 12 && j == 11) || (i == 13 && j == 10) ||
                (i == 14 && j == 7) || (i == 14 && j == 9) ||
                (i == 14 && j == 10) || (i == 14 && j == 11) ||
                (i == 15 && j == 8) || (i == 15 && j == 10) ||
                (i == 15 && j == 12) || (i == 16 && j == 13) ||
                (i == 16 && j == 10) || (i == 17 && j == 9) ||
                (i == 17 && j == 11) || (i == 18 && j == 9) ||
                (i == 18 && j == 11)
            )
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }
}


// get number of alive neighbours at position (row, col)
static int alive_neighbours(int matrix[][MATRIX_SIZE], int row, int col) {
    int counter = 0;
    int i, j;

    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++)
            counter += matrix[i][j];
    }

    counter -= matrix[row][col];
    return counter;
}


// get matrix state at time + 1
static void update_matrix(int matrix[][MATRIX_SIZE]) {
    int i, j;
    int neighbours;
    int density_matrix[SUB_MATRIX_SIZE][SUB_MATRIX_SIZE];

    for (i = 0; i < SUB_MATRIX_SIZE; i++) {
        for (j = 0; j < SUB_MATRIX_SIZE; j++) {
            density_matrix[i][j] = alive_neighbours(matrix, i + 1, j + 1);
        }
    }

    for (i = 0; i < SUB_MATRIX_SIZE; i++) {
        for (j = 0; j < SUB_MATRIX_SIZE; j++) {
            neighbours = density_matrix[i][j];
            if (matrix[i + 1][j + 1] == 1) {
                if (neighbours <= 1 || neighbours >= 4)
                    matrix[i + 1][j + 1] = 0;
                else
                    matrix[i + 1][j + 1] = 1;
            }
            else {
                if (neighbours == 3)
                    matrix[i + 1][j + 1] = 1;
                else
                    matrix[i + 1][j + 1] = 0;
            }
        }
    }
}


// display current matrix
static void display_matrix(int matrix[][MATRIX_SIZE]) {
    int i, j;

    for (i = 1; i <= SUB_MATRIX_SIZE; i++) {
        line_return(SUB_MATRIX_SIZE);
        for (j = 1; j <= SUB_MATRIX_SIZE; j++) {
            if (matrix[i][j] == 1)
                printf("|%c", '*');
            else
                printf("|%c", ' ');
        }
        printf("|\n");
    }
    line_return(SUB_MATRIX_SIZE);
}


// print a line
static void line_return(int width) {
    int i;
    for (i = 0; i < width; i++)
        printf("+-");
    printf("+\n");
}
