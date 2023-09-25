#include <iostream>
#include <chrono>

using namespace std;

void matrix_multiply_classic(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_blocks(int **A, int **B, int **C, int n, int block_size) {
    int i, j, k, ii, jj, kk;
    for (i = 0; i < n; i += block_size) {
        for (j = 0; j < n; j += block_size) {
            for (k = 0; k < n; k += block_size) {
                for (ii = i; ii < i + block_size; ii++) {
                    for (jj = j; jj < j + block_size; jj++) {
                        for (kk = k; kk < k + block_size; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {

    int block_size = 100;
    for (int n = 100; n <= 500; n += 100) {


        int **A = new int*[n];
        int **B = new int*[n];
        int **C = new int*[n];
        for (int i = 0; i < n; i++) {
            A[i] = new int[n];
            B[i] = new int[n];
            C[i] = new int[n];
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
                C[i][j] = 0;
            }
        }

        auto start = chrono::high_resolution_clock::now();
        matrix_multiply_classic(A, B, C, n);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "Multiplicación de matrices clásica: " << n << ": " << duration << " microsegundos" << endl;

       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
            }
        }

        start = chrono::high_resolution_clock::now();
        matrix_multiply_blocks(A, B, C, n, block_size);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "Multiplicación de matrices por bloques (" << block_size << "x" << block_size << "): " << duration << " microsegundos" << endl;

        
        for (int i = 0; i < n; i++) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }

    return 0;
}

