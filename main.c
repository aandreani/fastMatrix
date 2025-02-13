#include <time.h> // performance analysis
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "fastMatrix.h"

int main() {
    printf("Welcome to fastMatrix library test!\n");

    printf("[+] Allocating some matrices...");
    matrix* A = new_matrix(10, 10000);
    matrix* B = new_matrix(10000, 5);
    init_matrix(A); init_matrix(B);
    printf("done!\n");

    clock_t t;
    double tt;

    printf("*** Matrix mul test section ***\n");

    matrix* ab = new_matrix(A->r, B->c);
    matrix* fab = new_matrix(A->r, B->c);
    matrix* T = new_matrix(B->c, B->r);

    
    printf("[+] Computing E x F (%dx%d, %dx%d):\n", 
        A->r, A->c, B->r, B->c);

    t = clock();
    mul(A->m, B->m, ab->m, A->r, B->c, B->r);
    t = clock()-t;
    tt = ((double)t)/CLOCKS_PER_SEC;
    printf("slow: %f\t", tt);

    t = clock();
    mul_t(A->m, B->m, fab->m, T->m, A->r, B->c, B->r);
    t = clock()-t;
    tt = ((double)t)/CLOCKS_PER_SEC;
    printf("fast: %f\t\n", tt);
    

    printf("[+] Cleaning memory...");
    delete_matrix(A);
    delete_matrix(B);
    delete_matrix(ab);
    delete_matrix(fab);
    printf("done!\n");
}
