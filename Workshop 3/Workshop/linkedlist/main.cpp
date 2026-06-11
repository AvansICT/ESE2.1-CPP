// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "linkedlist.hpp"
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::cout << "Workshop 3!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime

    LinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);

    std::cout << "Beginlijst: ";
    list.print();

    list.insertFront(5);
    std::cout << "Na insertFront(5): ";
    list.print();

    list.insertAt(1, 15);  // Voeg 15 in op index 1
    std::cout << "Na insertAt(1,15): ";
    list.print();

    list.remove(20);
    std::cout << "Na remove(20): ";
    list.print();

    list.remove(5);
    std::cout << "Na remove(5): ";
    list.print();

    return 0;
}
