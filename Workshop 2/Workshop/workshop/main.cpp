// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>   // voor binair
#include <iomanip>  // voor hex
#include "log.hpp"
#include "robot.hpp"

using namespace std;
using namespace avans;

// use #define to select which code is compiled
//#define STACKOVERFLOW_RECURSIVE
//#define STACKOVERFLOW_STACKSIZE

// Uitvoer kan verschillen per systeem
void sizeofDemo(void) {

    //Voorbeeld 1 – Basisgebruik
    cout << "int: " << sizeof(int) << " bytes\n";
    cout << "double: " << sizeof(double) << " bytes\n";
    cout << "long: " << sizeof(long) << " bytes\n";
    cout << "char: " << sizeof(char) << " bytes\n";
    cout << "void*: " << sizeof(void*) << " bytes\n";

    int x = 42;
    cout << "variabele x: " << sizeof(x) << " bytes\n";
    //Voorbeeld 2 – Arrays
    int arr[10];
    cout << sizeof(arr) << " bytes\n";             // meestal 40 (10 * 4)
    cout << sizeof(arr) / sizeof(arr[0]) << endl;  // aantal elementen = 10

    struct Point {
        int x;
        int y;
        void* p;  // depend on platform (x86 (32bit):4 or x64 (64bit):8 bytes)
    };

    cout << "sizeof(Point) = " << sizeof(Point) << " bytes\n";

    struct A {
        char c;   // 1 byte
        int i;    // 4 bytes
        void* p;  // depend on platform (x86 (32bit):4 or x64 (64bit):8 bytes)
    };

    cout << "sizeof(A) = " << sizeof(A) << endl;
    std::cout << "offset c = " << offsetof(A, c) << "\n";
    std::cout << "offset i  = " << offsetof(A, i) << "\n";
    std::cout << "offset p  = " << offsetof(A, p) << "\n";

    struct B {
        void* p; // depend on platform (x86 (32bit):4 or x64 (64bit):8 bytes)
        int i;   // 4 bytes
        char c;  // 1 byte
    };
    cout << "sizeof(B) = " << sizeof(B) << endl;
    std::cout << "offset p  = " << offsetof(B, p) << "\n";
    std::cout << "offset c = " << offsetof(B, c) << "\n";
    std::cout << "offset i  = " << offsetof(B, i) << "\n";

    struct C {
        char c1;  // 1 byte
        double d; // 8 bytes
        char c2;  // 1 byte
    };
    cout << "sizeof(C) = " << sizeof(C) << endl;
    std::cout << "offset c1 = " << offsetof(C, c1) << "\n";
    std::cout << "offset d  = " << offsetof(C, d) << "\n";
    std::cout << "offset c2 = " << offsetof(C, c2) << "\n";
}

void pointerDemo(void)
{
    int a = 42;
    int b;
    int* p;

    std::cout << "Waarde van a: " << a << "\n";
    p = &a;     // p bevat nu het adres van a
    std::cout << "Adres van a: " << &a << "\n";
    std::cout << "Adres van a: " << p << "\n";
    b = *p;     // b bevat nu de waarde op adres p
    std::cout << "Waarde van b: " << a << "\n";
    *p = 99;    // op adres p staat nu de waarde 99
    std::cout << "Waarde van a: " << a << "\n";
    std::cout << "Waarde van b: " << b << "\n";

    int x = 42;
    int* ptr = &x;  // pointer naar x

    std::cout << "Waarde van x: " << x << "\n";
    std::cout << "Adres van x: " << &x << "\n";
    std::cout << "Waarde via pointer: " << *ptr << "\n";

    *ptr = 100; // verander waarde via pointer
    std::cout << "Nieuwe waarde van x: " << x << "\n";
}

void staticArrayDemo()
{
    // pointers en arrays
    // een array is een opeenvolging van elementen van hetzelfde type
    // int* arr; is feitelijk hetzelfde als int arr[];
    int arr[5] = { 10, 20, 30, 40, 50 };
    int arr1[5];
    int arr2[] = { 15, 26, -67, 4756, 99 };
    float matrix[10][12];   // initialisatie niet verplicht, inhoud compiler afhankelijk

    int* pArr = arr; // of int* pArr = &arr[0];
    std::cout << "Eerste element van array: " << *pArr << "\n"; // 10
    std::cout << "Eerste element van array: " << arr[0] << "\n"; // 10
}

#if defined(STACKOVERFLOW_RECURSIVE)
void testRecursiveStackOverflow(void)
{
    volatile int x[1024];
    (void)x;
    testRecursiveStackOverflow();    // infinite recursion force stack overflow
}
#elif defined(STACKOVERFLOW_STACKSIZE)
void testStackSizeStackOverflow(void)
{
    // This project has been configured to use a fixed stack of 4MB.
    // Project -> Properties -> Configuration Properties -> Linker -> System -> Stack Reserve Size=4194304 (4*1024*1024). 
    int largeArray[1024*1024*5];// allocate 5MB array on stack to force stack overflow
    largeArray[0] = 1; // use the array to avoid optimization
    std::cout << "Large array allocated on stack, first element: " << largeArray[0] << std::endl;   
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Workshop 2!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    sizeofDemo();
    pointerDemo();
    staticArrayDemo();
#if defined(STACKOVERFLOW_RECURSIVE)
    testRecursiveStackOverflow();
#elif defined(STACKOVERFLOW_STACKSIZE)
    testStackSizeStackOverflow();
#endif

    Robot r(0x7F000001); //127.0.0.1
    return 0;
}
