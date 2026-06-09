// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <print>    //C++23
#include "log.hpp"
#include "rekenen.hpp"

using namespace std;
using namespace rekenen;

#define FIRSTNUM    5
#define SECONDNUM   6

// Global function
int globalAdd(int x, int y) {
    return x + y;
}

int main()
{
    std::cout << "Hello World!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    std::print("Hello, World! C++23\n");    // C++23 feature
    LogCxxStandard();
    LogOperatingSystem();
    LogCompiler();
    LOG_DEBUG;

    int sum = globalAdd(5, 6);  // global function
    sum = rekenen::add(5, 6);   // namespace function
    Rekenen r;                  // class constructor
    sum = r.add(5, 6);          // class method

    if (sum > 10) {
        std::cout << "Meer dan tien" << std::endl;
    } else {
        std::cout << "Minder dan tien" << std::endl;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
