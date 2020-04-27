typedef struct matrix {
    int ** m;
    int r;
    int c;
} matrix;

matrix* new_matrix(int r, int c);

void init_matrix(matrix* mat);

void print_matrix(matrix* mat);

void delete_matrix(matrix* mat);

void matrix_sum(matrix* A, matrix* B, matrix* C);

matrix* transpose(matrix* A);