#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "Workshop 6!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    return 0;
}
