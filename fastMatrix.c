#include "fastMatrix.h"
#include <immintrin.h>
#include <stdlib.h>
#include <assert.h>

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
void mul_t(int** A, int** B, int** C, int** T, int ar, int bc, int br) {
    int i = 0, j, k;

    for(i=0; i < br; i++) {
        for(j=0; j<bc; j++) T[j][i] = B[i][j];
    }
    __m256i tmp = _mm256_set_epi32(0,0,0,0,0,0,0,0);
    int cc[8];
    for(i=0; i < ar; i++) {
        for(j=0; j<bc; j++) {
            for(k=0; k+7<br; k+=8) {
                __m256i a, b, c;
                a = _mm256_loadu_si256((const __m256i*)(A[i]+k));
                b = _mm256_loadu_si256((const __m256i*)(T[j]+k));
                tmp = _mm256_add_epi32(tmp, _mm256_mullo_epi32(a, b));
            }
            _mm256_storeu_si256((__m256i*)cc, tmp);
            int sum = 0;
            for(k; k<br; k++) sum += A[i][k]*T[j][k];
            C[i][j] = sum;
            for(k=0; k<8; k++) C[i][j] += cc[k];
        }
    }
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
