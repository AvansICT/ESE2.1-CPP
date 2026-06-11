#include <vector>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "log.hpp"
#include "omptimer.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "windowstimer.hpp"
#elif defined(__linux__)
#include "linuxtimer.hpp"
#else
#error implement system specific timer or use generic timer
#endif

#define FIBONACCI_NR 45

// Sequential recursive Fibonacci
long long fibonacci(long long n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 2) + fibonacci(n - 1);
}

// Recursive Fibonacci with OpenMP tasks
long long fibonacciOpenMP(int n) {
    if (n <= 1) return n;

    long long x, y;
#pragma omp task shared(x) if(n > 20)
    x = fibonacciOpenMP(n - 1);

#pragma omp task shared(y) if(n > 20)
    y = fibonacciOpenMP(n - 2);

#pragma omp taskwait
    return x + y;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "OpenMP Fibonacci!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl;
    LogOperatingSystem();
    LogCompiler();
    LogCxxStandard();

#if defined(_WIN32) || defined(_WIN64)
    WindowsTimer t1;
#elif defined(__linux__)
    LinuxTimer t1;
#else
#error implement system specific timer or use generic timer
#endif

    OmpTimer t2;

    long long result_seq;
    std::vector<long long> results_seq(FIBONACCI_NR);

    // ================= Sequential =================
    std::cout << "\nSequential Fibonacci\n";

    // Single fibonacci(N)
    t1.startTimer();
    result_seq = fibonacci(FIBONACCI_NR);
    t1.stopTimer();
    std::cout << "Sequential fibonacci(" << FIBONACCI_NR << ") = " << result_seq
        << ", Time = " << t1.elapsedTime() << " sec\n";

    // Whole sequence
    t1.startTimer();
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        results_seq[i - 1] = fibonacci(i);
    }
    t1.stopTimer();
    int idx = 1;
    std::for_each(results_seq.begin(), results_seq.end(), [&](long long val) {
        std::cout << "Fib(" << idx++ << ") = " << val << std::endl;
        });
    std::cout << "Sequential elapsed: " << t1.elapsedTime() << " sec\n";

    // ================= Parallel =================
    int iCPU = omp_get_num_procs();
    std::cout << "\nUsing number of cores: " << iCPU << std::endl;
    omp_set_num_threads(iCPU);

    std::vector<long long> results_par(FIBONACCI_NR);
    long long result_par;

    // ---- Parallel single fibonacci(N) with tasks
    std::cout << "\nParallel Fibonacci (single value)\n";
    t2.startTimer();
#pragma omp parallel
    {
#pragma omp single
        result_par = fibonacciOpenMP(FIBONACCI_NR);
    }
    t2.stopTimer();
    std::cout << "Parallel OpenMP fibonacci(" << FIBONACCI_NR << ") = " << result_par
        << ", Time = " << t2.elapsedTime() << " sec\n";

    // ---- Parallel sequence (method 1: for loop)
    std::cout << "\nParallel Fibonacci sequence (for loop)\n";
    t2.startTimer();
#pragma omp parallel for
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        results_par[i - 1] = fibonacciOpenMP(i);
    }
    t2.stopTimer();
    idx = 1;
    for (const auto& val : results_par) {
        std::cout << "Fib(" << idx++ << ") = " << val << std::endl;
    }
    std::cout << "Parallel OpenMP (for) elapsed: " << t2.elapsedTime() << " sec\n";

    // ---- Parallel sequence (method 2: tasks)
    std::cout << "\nParallel Fibonacci sequence (tasks)\n";
    t2.startTimer();
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 1; i <= FIBONACCI_NR; i++) {
#pragma omp task firstprivate(i)
                results_par[i - 1] = fibonacciOpenMP(i);
            }
        }
    }
    t2.stopTimer();
    idx = 1;
    for (const auto& val : results_par) {
        std::cout << "Fib(" << idx++ << ") = " << val << std::endl;
    }
    std::cout << "Parallel OpenMP (tasks) elapsed: " << t2.elapsedTime() << " sec\n";

    return 0;
}
