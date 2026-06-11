// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
// GCC versie check voor C++23 std::print ondersteuning
#if defined(__GNUC__) && (__GNUC__ < 13)
#define NO_STD_PRINT
#endif

#ifndef NO_STD_PRINT
#include <print>
#endif

#include "log.hpp"
#include "rekenen.hpp"

using namespace std;
using namespace MijnRekenNamespace;

#define FIRSTNUM    5
#define SECONDNUM   6

// Global function
int globalAdd(int x, int y) {
    return x + y;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Hello World!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime

#ifdef NO_STD_PRINT
    std::cout << "std::print not supported on this GCC version\n";
#else
    std::print("Hello, World! C++23\n");    // C++23 feature
#endif
    LogTargetCxxStandard();
    LogTargetOperatingSystem();
    LogTargetCompiler();
    LOG_DEBUG;

    int sum = globalAdd(40, 2);  // global function
    std::cout << "globalAdd: " << sum << std::endl;
    sum = MijnRekenNamespace::NameSpaceAdd(40, 2);        // namespace function
    std::cout << "NameSpaceAdd: " << sum << std::endl;
    sum = NameSpaceAdd(40, 2);        // namespace function
    std::cout << "NameSpaceAdd: " << sum << std::endl;

    MijnRekenNamespace::MijnRekenKlasse r;      // class constructor
    MijnRekenKlasse r2;
    sum = r.add(40, 2);          // class method
    std::cout << "Class method sum: " << sum << std::endl;
    sum += r2.add(40, 2);         // class method
    std::cout << "Class method sum: " << sum << std::endl;

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
