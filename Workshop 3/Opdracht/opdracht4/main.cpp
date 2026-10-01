#include <iostream>
// C++ versie check voor C++23 std::print ondersteuning
#if (__cplusplus < 202302L)
#define NO_STD_PRINT
#endif

#ifndef NO_STD_PRINT
#include <print>
#endif
#include "log.hpp"

using namespace std;

class Student {
private:
    const int studentId;       // kan niet aangepast worden na constructie
    static int aantalStudenten; // gedeeld door alle Student-objecten

public:
    Student(int id) : studentId(id) {
        // TODO: verhoog aantalStudenten
    }

    int getStudentId() const {
        // TODO: retourneer de ID
		return 0; // placeholder
    }

    static int getAantalStudenten() {
        // TODO: retourneer aantalStudenten
		return 0; // placeholder
    }
};

// TODO: initialiseer static variabele

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifdef NO_STD_PRINT
    std::cout << "std::print not supported on this C++ version\n";
#else
    std::print("Hello, Opdracht 4\n");    // C++23 feature
#endif
    Student s1(101);
    Student s2(102);

    cout << "Student 1 ID: " << s1.getStudentId() << endl;
    cout << "Student 2 ID: " << s2.getStudentId() << endl;

    cout << "Totaal aantal studenten: " << Student::getAantalStudenten() << endl;
}
