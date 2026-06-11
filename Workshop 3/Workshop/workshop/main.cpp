// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "log.hpp"
#include "robot.hpp"

struct data {
    int i;
    bool b;
};

// Notatie: pointer naar een struct gebruiken
void demo1(void) {
    struct data s;
    struct data* p;
    p = &s;
    s.i = 42;
    s.b = true;

    std::cout << s.i << " " << (s.b ? 1 : 0) << '\n'; // 42 1
    p->i = 43;
    std::cout << s.i << " " << (s.b ? 1 : 0) << '\n'; // 43 1
    p->b = false;
    std::cout << s.i << " " << (s.b ? 1 : 0) << '\n'; // 43 0
}

void changeCallByValue(int x) {
    x = 2; // verandert alleen de kopie
}

void changeCallByReference(int& x) {
    x = 3; // werkt direct op 'a'
}

void changeCallByValuePtr(int* p) {
    *p = 4; // via de pointer veranderen we de originele variabele
}

void changePointer(int*& p) {
    static int other = 123;
    p = &other; // laat pointer naar iets anders wijzen
}

// call by reference / call by value
void demo2(void) {
    int a = 1;
    int* ptr = &a;
    changeCallByValue(a);       // Call by Value
    std::cout << a << std::endl;          // output: 1
    changeCallByReference(a);   // Call by Reference (voorkeur)
    std::cout << a << std::endl;          // output: 3
    changeCallByValuePtr(&a);   // Pointer doorgeven (Call by Value met pointer)
    std::cout << a << std::endl;          // output: 4
    changePointer(ptr);         // Pointer by Reference (Call by Reference met pointer)
    std::cout << *ptr << std::endl;       // output: 123
}

void renameCallByValue(Robot r) {
    r.name = "Copied";
}

void renameCallByReference(Robot& r) {
    r.name = "Beta";
}

void renameByPointer(Robot* r) {
    r->name = "Gamma";
}

void pointToNewRobot(Robot*& r) {
    static Robot newBot("Delta");
    r = &newBot; // pointer wijst nu naar een ander object
}
// call by reference / call by value
void demo3(void) {
    Robot a("Alpha");
    Robot* ptr = &a;
    renameCallByValue(a);   // Call by Value kopie van object
    cout << a.name << endl; // output: Alpha
    renameCallByReference(a);
    cout << a.name << endl;  // Output: Beta
    renameByPointer(ptr);
    cout << a.name << endl;  // Output: Gamma
    pointToNewRobot(ptr);
    cout << ptr->name << endl;  // Output: Delta
}

void counter(void) {
    static int count = 0;  // wordt slechts één keer geïnitialiseerd
    count++;
    cout << "Count = " << count << endl;
}

void demo4(void) {
    counter();  // Count = 1
    counter();  // Count = 2
    counter();  // Count = 3
}


class RobotDemo {
public:
    static int robotCount;  // telt alle robots
    RobotDemo() { robotCount++; }
    static void greet() {
        cout << "Hello from Robot class!" << endl;
    }
};

int RobotDemo::robotCount = 0;  // definitie van static member

void demo5(void) {
    RobotDemo r1, r2, r3;
    std::cout << "Aantal robots: " << RobotDemo::robotCount << std::endl; // 3
}

void demo6(void) {
    RobotDemo::greet();  // kan zonder object
}

static int secret = 42;  // enkel zichtbaar in dit bestand

static void secretFunc(void) {
    std::cout << "Dit is geheime functie!" << std::endl;
}

void demo7(void) {
    secretFunc();
	std::cout << "Geheime waarde: " << secret << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "Workshop 3!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    demo1();
    demo2();
    demo3();
    // static demo
    demo4();
    demo5();
    demo6();
	demo7();
    return 0;
}
