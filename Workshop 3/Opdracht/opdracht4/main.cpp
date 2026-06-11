#include <iostream>
#include <print>    //C++23
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
    std::print("Hello, Opdracht 4\n");    // C++23 feature
    Student s1(101);
    Student s2(102);

    cout << "Student 1 ID: " << s1.getStudentId() << endl;
    cout << "Student 2 ID: " << s2.getStudentId() << endl;

    cout << "Totaal aantal studenten: " << Student::getAantalStudenten() << endl;
}
