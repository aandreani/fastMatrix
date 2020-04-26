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

int main() {
    printf("Welcome to fastMatrix library test!\n");
    printf("[+] Allocating some matrices...");
    matrix* A = new_matrix(2, 2);
    matrix* B = new_matrix(2, 2);
    matrix* C = new_matrix(5, 5);
    matrix* D = new_matrix(5, 5);
    matrix* E = new_matrix(4, 44);
    matrix* F = new_matrix(4, 44);
    init_matrix(A); init_matrix(B);
    init_matrix(C); init_matrix(D);
    init_matrix(E); init_matrix(F);
    printf("done!\n");

    printf("A:\n");
    print_matrix(A);
    printf("B:\n");
    print_matrix(B);

    printf("*** Matrix sum test section ***\n");
    printf("Computing some sums...");
    matrix* ab = new_matrix(A->r, A->c);
    sum_int_matrix(A->m, B->m, ab->m, A->r, A->c);

    matrix* cd = new_matrix(C->r, C->c);
    sum_int_matrix(C->m, D->m, cd->m, C->r, C->c);

    matrix* ef = new_matrix(E->r, E->c);
    sum_int_matrix(E->m, F->m, ef->m, E->r, E->c);
    printf("done!\n");

    printf("A + B:\n"); print_matrix(ab);
    printf("C + D:\n"); print_matrix(cd);
    printf("E + F:\n"); print_matrix(ef);


    printf("[+] Cleaning memory...");
    delete_matrix(A);
    delete_matrix(B);
    delete_matrix(C);
    delete_matrix(D);
    delete_matrix(E);
    delete_matrix(F);
    printf("done!");
}