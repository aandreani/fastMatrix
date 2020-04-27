#include <time.h> // performance analysis
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "fastMatrix.h"

int main() {
    printf("Welcome to fastMatrix library test!\n");

    printf("[+] Allocating some matrices...");
    matrix* A = new_matrix(2, 2);
    matrix* B = new_matrix(2, 2);
    matrix* C = new_matrix(5, 5);
    matrix* D = new_matrix(5, 5);
    matrix* E = new_matrix(10000, 1000000);
    matrix* F = new_matrix(10000, 1000000);
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
    printf("[+] Computing times for E + F (%dx%d):\n", E->r, E->c);

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