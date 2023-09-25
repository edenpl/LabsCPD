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

void matrix_multiply_three_loops(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
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
        cout << "Multiplicación de matrices clásica para n=" << n << ": " << duration << " microsegundos" << endl;

        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
            }
        }

        start = chrono::high_resolution_clock::now();
        matrix_multiply_three_loops(A, B, C, n);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "Multiplicación de matrices con tres bucles anidados para n=" << n << ": " << duration << " microsegundos" << endl;

        
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

