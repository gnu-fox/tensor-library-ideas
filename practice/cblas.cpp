#include <iostream>
#include <cstdlib>  // For malloc/free
#include <cblas.h>  // CBLAS header

int main() {
    // Define matrix dimensions
    int m = 3;  // Number of rows in A
    int n = 2;  // Number of columns in A, number of rows in B
    int k = 4;  // Number of columns in B

    // Allocate memory for matrices A, B, and C
    double *A = (double *)std::malloc(m * n * sizeof(double));
    double *B = (double *)std::malloc(n * k * sizeof(double));
    double *C = (double *)std::malloc(m * k * sizeof(double));

    // Initialize matrices A and B
    for (int i = 0; i < m * n; i++) {
        A[i] = i + 1;
    }

    for (int i = 0; i < n * k; i++) {
        B[i] = i + 1;
    }

    // Perform matrix multiplication: C = A * B
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, k, n, 1.0, A, n, B, k, 0.0, C, k);

    // Print the result matrix C
    std::cout << "Result Matrix C:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            std::cout << C[i * k + j] << " ";
        }
        std::cout << "\n";
    }

    // Free dynamically allocated memory
    std::free(A);
    std::free(B);
    std::free(C);

    return 0;
}
