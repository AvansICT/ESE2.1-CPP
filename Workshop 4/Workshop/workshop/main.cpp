// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "log.hpp"

class InheritanceBase {
public:
    void sayHello() {
        std::cout << "Hello from InheritanceBase!" << std::endl;
    }
};

class InheritanceDerived : public InheritanceBase {   // Derived erft van Base
public:
    void sayBye() {
        std::cout << "Goodbye from InheritanceDerived!" << std::endl;
    }
};

static void demonstrateInheritance() {
    InheritanceDerived d;
    d.sayHello(); // Inherited method from Base
    d.sayBye();   // Method from Derived
}

class A {
public:
    void greet() { std::cout << "Hello from A\n"; }
};

class B {
public:
    void greet() { std::cout << "Hello from B\n"; }
};

class C : public A, public B {
public:
	void greetC() { std::cout << "Hello from C\n"; }
};

static void demonstrateMultipleInheritance(void) {
    C obj;
    // obj.greet(); // fout: ambigu, A::greet of B::greet?
    obj.A::greet(); // correct, expliciet A
    obj.B::greet(); // correct, expliciet B
    obj.greetC();
}

class PolymorphismBase {
public:
    virtual void greet() { std::cout << "Hello from PolymorphismBase\n"; }
};

class PolymorphismDerived1 : public PolymorphismBase {
public:
};

class PolymorphismDerived2 : public PolymorphismBase {
public:
    void greet() override { std::cout << "Hello from Derived override\n"; }
};

static void demonstratePolymorphism(void) {
    PolymorphismBase* obj1 = new PolymorphismDerived1();
    obj1->greet();  // Roept PolymorphismBase::greet() aan
    PolymorphismBase* obj2 = new PolymorphismDerived2();
    obj2->greet();  // Roept PolymorphismDerived2::greet() aan
    delete obj1,obj2;
}

static void demonstrateLambda(void) {
	auto add = [](int a, int b) { return a + b; };
	std::cout << "Lambda add(2, 3): " << add(2, 3) << std::endl;
}

// Classic Function pointer example
typedef int(*myFunctionpoiter)(int, int);

// Prototype
int addClassicFPInt(int x, int y);
int addIntWithClassicFP(int x, int y, myFunctionpoiter fp); //Vervangt: int addIntWithFP(int x, int y, int(*fp)(int, int));

void demonstrateClassicFP() {
    std::cout << "resultaat: " << addIntWithClassicFP(1, 2, addClassicFPInt) << std::endl;
}

int addClassicFPInt(int x, int y) {
    return x + y;
}

int addIntWithClassicFP(int x, int y, myFunctionpoiter fp) {
    return fp(x, y);
}

#include <functional> // voor std::function
// Prototype
int addInt(int x, int y);
int addIntWithFP(int x, int y, std::function<int(int, int)> func);

int demonstrateStdFunctionFP() {
    std::cout << "Resultaat: " << addIntWithFP(1, 2, addInt) << std::endl;

    // Bonus: ook een lambda kan erin
    std::cout << "Resultaat lambda: "
        << addIntWithFP(3, 4, [](int a, int b) { return a * b; })
        << std::endl;

    return 0;
}

int addInt(int x, int y) {
    return x + y;
}

int addIntWithFP(int x, int y, std::function<int(int, int)> func) {
    return func(x, y);
}


// Een functor-klasse die optelt
struct Add {
    int operator()(int a, int b) const {
        return a + b;
    }
};

// Een functor-klasse die vermenigvuldigt
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

void demonstrateStdFunctionFunctor() {
    // std::function kan ook functors opslaan
    std::function<int(int, int)> func;

    func = Add(); // gebruik de Add functor
    std::cout << "5 + 3 = " << func(5, 3) << std::endl;

    func = Multiply(); // gebruik de Multiply functor
    std::cout << "5 * 3 = " << func(5, 3) << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "Workshop 4!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    demonstrateInheritance();
    demonstrateMultipleInheritance();
    demonstratePolymorphism();
    demonstrateLambda();
    demonstrateClassicFP();
    demonstrateStdFunctionFP();
    return 0;
}
