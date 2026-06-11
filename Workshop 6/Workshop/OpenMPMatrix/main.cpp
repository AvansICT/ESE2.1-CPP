#include <iostream>
#include <vector>
#include <omp.h>
#include "omptimer.hpp"
#include "chronotimer.hpp"

#define MATRIX_SIZE 999 // grootte van de matrix

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "OpenMPMatrix!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    ChronoTimer t1;
    OmpTimer t2;
    const int N = MATRIX_SIZE; 
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 1.0));
    std::vector<std::vector<double>> B(N, std::vector<double>(N, 2.0));
    std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

    // --------- Sequentieel ---------
    t1.startTimer();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    t1.stopTimer();
    std::cout << "Sequentieel: " << t1.elapsedTime() << " s\n";

    // Reset C
    for (int i = 0; i < N; i++)
        std::fill(C[i].begin(), C[i].end(), 0.0);

    // --------- Parallel met OpenMP ---------
    int iCPU = omp_get_num_procs(); // Get the number of processors in this system
    std::cout << "Using number of cores: " << iCPU << std::endl;
    omp_set_num_threads(iCPU); // Now set the number of threads
    t2.startTimer();
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    t2.stopTimer();
    std::cout << "Parallel (OpenMP): " << t2.elapsedTime() << " s\n";
    return 0;
}
