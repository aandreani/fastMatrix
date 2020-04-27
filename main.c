#include "fastMatrix.h"
#include <stdio.h>
#include <stdlib.h>

#include <time.h> // performance analysis

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

int main() {
    printf("Welcome to fastMatrix library test!\n");
    printf("[+] Allocating some matrices...");
    matrix* A = new_matrix(2, 2);
    matrix* B = new_matrix(2, 2);
    matrix* C = new_matrix(5, 5);
    matrix* D = new_matrix(5, 5);
    matrix* E = new_matrix(10000, 1024);
    matrix* F = new_matrix(10000, 1024);
    init_matrix(A); init_matrix(B);
    init_matrix(C); init_matrix(D);
    init_matrix(E); init_matrix(F);
    printf("done!\n");

    printf("A:\n");
    print_matrix(A);
    printf("B:\n");
    print_matrix(B);

    clock_t t;
    double tt;

    printf("*** Matrix sum test section ***\n");

    matrix* ef = new_matrix(E->r, E->c);
    matrix* sef = new_matrix(E->r, E->c);
    printf("[+] Computing times for E + F (512x1024):\n");

    t = clock();
    matrix_sum(E, F, sef);
    t = clock()-t;
    tt = ((double)t)/CLOCKS_PER_SEC;
    printf("slow: %f\t", tt);

    t = clock();
    sum_int_matrix(E->m, F->m, ef->m, E->r, E->c);
    t = clock()-t;
    tt = ((double)t)/CLOCKS_PER_SEC;
    printf("fast: %f\t\n", tt);


    printf("[+] Cleaning memory...");
    delete_matrix(A);
    delete_matrix(B);
    delete_matrix(C);
    delete_matrix(D);
    delete_matrix(E);
    delete_matrix(F);
    delete_matrix(ef);
    delete_matrix(sef);
    printf("done!\n");
}