// This library is made for fast matrix operations
// By fast I mean accelerated with sse or avx intrinsics

/*
 * @param A: first operand
 * @param B: second operand
 * @param C: empty matrix of the same size of A or B
 * @param r: number of rows of matrix A
 * @param c: number of columns of matrix A
 * ATTENTION! Pass same sized matrix, since no control will be made
 * on their size and buffer overflow / segmentation fault could happen.
*/
void sum_int(int** A, int** B, int** C, int r, int c);