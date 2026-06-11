#include <iostream>
#include <string>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "Workshop 6!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    return 0;
}
