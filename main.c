#include "fastMatrix.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix
{
    int ** m;
    int r;
    int c;
} matrix;


matrix* new_matrix(int r, int c) {
    matrix* ris = (matrix*)malloc(sizeof(matrix));
    ris->r = r;
    ris->c = c;
    int** m = (int**)malloc(r*sizeof(int*));
    int i = 0;
    for(i; i < r; i++) m[i] = (int*)calloc(c,sizeof(int));
    ris->m = m;
    return ris;
}

void init_matrix(matrix* mat) {
    int** m = mat->m;
    int i = 0, j = 0;
    for(i; i < mat->r; i++) for(j = 0; j < mat->c; j++) m[i][j] = 1;
}

void print_matrix(matrix* mat) {
    int** m = mat->m;
    int i = 0, j = 0;
    for(i; i < mat->r; i++) {
        for(j = 0; j < mat->c; j++) printf("%d ", m[i][j]);
        printf('\n');
    }
    printf("\n");
}

void delete_matrix(matrix* mat) {
    int** m = mat->m;
    int i = 0;
    for(i; i < mat->r; i++) free(m[i]);
    free(m);
    free(mat);
}

int main() {
    printf("Welcome to fastMatrix library test!\n");
    printf("Allocating some matrices...");
    matrix* A = new_matrix(2, 2);
    matrix* B = new_matrix(2, 2);
    init_matrix(A); init_matrix(B);
    print_matrix(A);
    print_matrix(B);
    delete_matrix(A);
    delete_matrix(B);
}