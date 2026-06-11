#include <iostream>
#include <thread>
#include <barrier>
#include <vector>

void worker(int id, std::barrier<>& sync_point) {
    std::cout << "Thread " << id << " starting step 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // simulatie werk

    // Wacht tot alle threads bij de barrier zijn
    sync_point.arrive_and_wait();

    std::cout << "Thread " << id << " starting step 2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50 * id)); // simulatie werk
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "ThreadingExampleBarrier\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl;
    const int num_threads = 3;

    // Barrier: wacht tot alle threads arriveeren
    std::barrier sync_point(num_threads);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i + 1, std::ref(sync_point));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads finished\n";
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    __debugbreak(); // hardcoded breakpoint for debug build only
#endif
    return 0;
}

