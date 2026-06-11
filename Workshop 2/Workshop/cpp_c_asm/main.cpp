// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// example of c / cpp mixed programming


#include <iostream>
#include "log.hpp"
#include "clog.h"
#include "crc.h"
#include "swap.hpp"
#include "bitdemo.hpp"

// Declare external functions(implemented in assembly)
extern "C" int addWithAsmX64(int a, int b);
extern "C" int addWithAsmX86(int a, int b);

#define FIRSTNUM    5
#define SECONDNUM   6

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	std::cout << "Hello CPP C ASM" << std::endl;
    LogTargetArchitecture();
    LogRunTimeArchitecture();
    LogTargetOperatingSystem();
    LogTargetCompiler();
    LogTargetCxxStandard();
    LogTargetCStandard();
    std::cout << __DATE__ << " " << __TIME__ << std::endl << std::endl; // log date and time of compilation, not runtime

    // demo of binary literals
    demoBinair();
    // demo of bitmask operations
    demoBitmask();
    // dem  o of hexadecimal literals
    demoHexadecimal();

    // Call assembly function to add two numbers    
    int a = FIRSTNUM, b = SECONDNUM;
#if defined(_M_X64)
    int sum = addWithAsmX64(a, b);
    std::cout << "Using x64 assembly function to add " << a << " + " << b << " = " << sum << std::endl;
#elif defined(_M_IX86)
    int sum = addWithAsmX86(a, b);
    std::cout << "Using x86 assembly function to add " << a << " + " << b << " = " << sum << std::endl;
#elif defined(__x86_64__)
    std::cout << "Hello CPP C ASM from x64 (GCC)!" << std::endl;
    int sum = addWithAsmX64(a, b);
    std::cout << "Using x64 assembly function to add " << a << " + " << b << " = " << sum <<
        std::endl;
#elif defined(__i386__)
    std::cout << "Hello CPP C ASM from x86 (GCC)!" << std::endl;
    int sum = addWithAsmX86(a, b);
    std::cout << "Using x86 assembly function to add " << a << " + " << b << " = " << sum <<
        std::endl;
#else
#error Platform not supported
#endif
    // call C function to test CRC calculation
    testcrc();
    // call C++ function to test BitSwap
    testSwap();

    return 0;
}