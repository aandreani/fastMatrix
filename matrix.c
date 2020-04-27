#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#define MAX 1000000


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
    for(i; i < mat->r; i++) 
        for(j = 0; j < mat->c; j++)
            m[i][j] = 1; //rand()%MAX + 1;
}

void print_matrix(matrix* mat) {
    int** m = mat->m;
    int i = 0, j = 0;
    for(i; i < mat->r; i++) {
        for(j = 0; j < mat->c; j++) printf("%d ", m[i][j]);
        printf("\n");
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

void matrix_sum(matrix* A, matrix* B, matrix* C) {
    int r = A->r, c = A->c;
    int i = 0, j;
    int** a = A->m, ** b = B->m, ** cc = C->m;
    for(i; i < r; i++) 
        for(j = 0; j < c; j++) cc[i][j] = a[i][j] + b[i][j];
}

matrix* transpose(matrix* A) {
    int r = A->r, c = A->c;
    matrix* R = new_matrix(r, c);
    int** m = R->m;
    int i = 0, j;
    for(i; i < r; i++) {
        for(j = 0; j < c; j++) m[i][j] = A->m[j][i];
    }
    return R;
}
