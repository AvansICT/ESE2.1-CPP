#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "log.hpp"
#include "chronotimer.hpp"
#if defined(_WIN32) || defined(_WIN64)
#include "windowstimer.hpp"
#elif defined(__linux__)
#include "linuxtimer.hpp"
#else
#error implement system specific timer or use generic timer
#endif


#define FIBONACCI_NR 45

std::unordered_map<long long, long long> fibCache;

inline long long fib_cache(long long n)
{
    auto it = fibCache.find(n);
    if (it != fibCache.end())
        return it->second;

    if (n <= 1)
    {
        return n;
    }

    auto fib = fib_cache(n - 1) + fib_cache(n - 2);
    fibCache[n] = fib;
    return fib;
}

long long fibonacci(long long n)
{
    if (n <= 1)
        return n;

    return fibonacci(n - 2) + fibonacci(n - 1);
}

int main(int argc, char* argv[])
{
    std::cout << "Fibonacci Sequence using C++!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogOperatingSystem();
    LogCompiler();

    std::vector<long long> results(FIBONACCI_NR);
    // fibonacci measured with chronotimer
    ChronoTimer t1;
    t1.startTimer();
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        results[i - 1] = fibonacci(i);
    }
    t1.stopTimer();
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        std::cout << "Fib(" << i << ") = " << results[i - 1] << std::endl;
    }
    std::cout << "t1 elapsed: " << t1.elapsedTime() << " sec\n";

    // fibonacci measured with windowtimer / linux timer

#if defined(_WIN32) || defined(_WIN64)
    WindowsTimer t2;
#elif defined(__linux__)
    LinuxTimer t2;
#else
#error implement system specific timer or use generic timer
#endif
    t2.startTimer();
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        results[i - 1] = fibonacci(i);
    }
    t2.stopTimer();
    for (int i = 1; i <= FIBONACCI_NR; i++) {
        std::cout << "Fib(" << i << ") = " << results[i - 1] << std::endl;
    }
    std::cout << "t2 elapsed: " << t2.elapsedTime() << " sec\n";

    // fibonacci without cache
    long long fib;
#if defined(_WIN32) || defined(_WIN64)
    WindowsTimer t3;
#elif defined(__linux__)
    LinuxTimer t3;
#else
#error implement system specific timer or use generic timer
#endif
    t3.startTimer();
    fib = fibonacci(FIBONACCI_NR);
    t3.stopTimer();
    std::cout << "Fibonacci without cache: " << fib << " took: " << t3.elapsedTime() << " sec\n";
    // fibonacci with cache
    long long fibC;
#if defined(_WIN32) || defined(_WIN64)
    WindowsTimer t4;
#elif defined(__linux__)
    LinuxTimer t4;
#else
#error implement system specific timer or use generic timer
#endif
    t4.startTimer();
    fibC = fib_cache(FIBONACCI_NR);
    t4.stopTimer();
    std::cout << "Fibonacci cached: " << fib << " took: " << t4.elapsedTime() << " sec\n";

    return 0;
}