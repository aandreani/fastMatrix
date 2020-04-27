#include "fastMatrix.h"
#include <immintrin.h>

void sum_4_int(int* A, int* B, int* C) {
    __m128i a, b, c;
	a = _mm_loadu_si128((const __m128i*)(A));
	b = _mm_loadu_si128((const __m128i*)(B));
	c = _mm_add_epi32(a,b);
	_mm_storeu_si128((__m128i*)C, c);
}

void sum_8_int(int* A, int* B, int* C) {
    __m256i a, b, c;
    a = _mm256_loadu_si256((const __m256i*)A);
    b = _mm256_loadu_si256((const __m256i*)B);
    c = _mm256_add_epi32(a, b);
    _mm256_storeu_si256((__m256i*)C, c);
}

void sum_int_matrix(int** A, int** B, int** C, int r, int c) {
    for(int i = 0; i < r; i++) {
        int j = 0;
        for(j; j+7 < c; j += 8) sum_8_int(A[i]+j, B[i]+j, C[i]+j);
        for(j; j+3 < c; j += 4) sum_4_int(A[i]+j, B[i]+j, C[i]+j);
        for(j; j < c; j++) C[i][j] = A[i][j] + B[i][j];
    }
}

// This functions need to be tested
// A: first operand
// B: second operand
// C: 0 initialized matrix
// ar = A rows
// bc = B cols
// br = A cols = B rows
void mul_t(int** A, int** B, int** C, int ar, int bc, int br) {
    int** m = (int**)malloc(bc*sizeof(int*));
    int i = 0, j, k;
    for(i; i < br; i++) m[i] = (int*)malloc(br*sizeof(int));

    for(i=0; i < br; i++) {
        for(j=0; j<bc; j++) m[i][j] = B[j][i];
    }
    int* tmp = (int*)malloc(br*sizeof(int));
    // Now m is the transposed matrix of B
    for(i = 0; i < ar; i++) {
        for(j = 0; j < bc; j++) {
            for(k = 0; k+7< br; k++) {
                __m256i aa, bb, cc;
                aa = _mm256_loadu_si256((const __m256i*)A[i]+k);
                bb = _mm256_loadu_si256((const __m256i*)m[i]+k);
                cc = _mm256_mullo_epi32(aa, bb);
                _mm256_storeu_si256((__m256i*)tmp+k, cc);
            }
            for(k; k<br; k++) tmp[k] = A[i][k]*m[i][k];
            for(k = 0; k < br; k++) C[i][j] += tmp[k];
        }
    }
    free(tmp);
    for(i=0;i<br;i++)free(m[i]);
    free(m);
}

// r = A rows
// c = B cols
// n = A cols = B rows
void mul(int** A, int** B, int** C, int r, int c, int n) {
    int i = 0, j, k;
    for(i; i < r; i++)
        for(j = 0; j < c; j++) {
            for(k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
        }
}
