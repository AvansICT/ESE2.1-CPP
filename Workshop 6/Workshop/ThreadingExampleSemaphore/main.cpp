#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <future>
#include <chrono>
#include <semaphore>   // C++20 counting_semaphore

enum LockType {
    None = 0,
    Mutex = 1,
    Semaphore = 2
};

// use a timed_mutex for mutex branch
std::timed_mutex localMutex;

// counting semaphore (max count = 2, initial count = 2)
std::counting_semaphore<2> localSemaphore(2);

using Ms = std::chrono::milliseconds;
using us = std::chrono::microseconds;

int square(int x) {
    return x * x;
}

void call_from_thread(int threadId, LockType lock) {
    if (lock == LockType::Mutex && !localMutex.try_lock_for(Ms(100)))
        return;

    if (lock == LockType::Semaphore) {
        if (!localSemaphore.try_acquire_for(Ms(1000)))
            return;
        std::stringstream ss;
        ss << "Acquire semaphore by thread " << threadId << std::endl;
        std::cout << ss.str();
    }

    std::stringstream ss1;
    ss1 << "Hello, World from thread: " << threadId << std::endl;
    std::cout << ss1.str();

    if (lock == LockType::Mutex)
        localMutex.unlock();

    if (lock == LockType::Semaphore)
        localSemaphore.release();
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "ThreadingExample C++20 version using std::counting_semaphore\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl;

    const int num_threads = 10;
    std::thread t[num_threads];

    // Launch a group of threads
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i, LockType::Semaphore);
        std::this_thread::sleep_for(us(50));
    }

    // Join the threads
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    __debugbreak();
#endif
    return 0;
}
