#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int data = 0;          // gedeeld item
bool ready = false;    // status van data

// Producer: maakt data klaar
void producer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulatie werk
    std::unique_lock<std::mutex> lock(mtx);
    data = 42;
    ready = true;
    std::cout << "Producer produced: " << data << "\n";
    cv.notify_one(); // wake up consumer
}

// Consumer: wacht tot data klaar is
void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []() { return ready; }); // wacht tot ready == true
    std::cout << "Consumer consumed: " << data << "\n";
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "ThreadingExampleConditionVariables\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl;
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    __debugbreak(); // hardcoded breakpoint for debug build only
#endif

    return 0;
}
