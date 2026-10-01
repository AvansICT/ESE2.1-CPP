// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
// C++ versie check voor C++23 std::print ondersteuning
#if (__cplusplus < 202302L)
#define NO_STD_PRINT
#endif

#ifndef NO_STD_PRINT
#include <print>
#endif
#include "log.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef NO_STD_PRINT
    std::cout << "std::print not supported on this C++ version\n";
#else
    std::print("Hello, Opdracht\n");    // C++23 feature
#endif

    return 0;
}
