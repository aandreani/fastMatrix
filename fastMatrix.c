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