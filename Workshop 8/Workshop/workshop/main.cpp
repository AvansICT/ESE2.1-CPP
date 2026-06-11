#include <iostream>
#include <vector>
#include "log.hpp"

// A simple template function that returns the maximum of two values
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// Template class for a simple pair (like std::pair)
template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    // Constructor
    Pair(T a, T b) : first(a), second(b) {}

    // Method to get the larger of the two
    T getMax() const {
        return (first > second) ? first : second;
    }

    // Method to display both values
    void show() const {
        std::cout << "First: " << first << ", Second: " << second << std::endl;
    }
};

// A generic stack class using templates
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (!elements.empty())
            elements.pop_back();
        else
            std::cout << "Stack is empty!" << std::endl;
    }

    T top() const {
        if (!elements.empty())
            return elements.back();
        throw std::out_of_range("Stack is empty");
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

void templateDemo(void)
{
    std::cout << "Template Demo Function\n";
    std::cout << getMax(10, 5) << std::endl;        // Works with int
    std::cout << getMax(3.14, 2.71) << std::endl;   // Works with double
    std::cout << getMax('a', 'z') << std::endl;     // Works with char


    Pair<int> intPair(10, 20);
    intPair.show();
    std::cout << "Max: " << intPair.getMax() << std::endl;

    Pair<double> doublePair(3.14, 2.71);
    doublePair.show();
    std::cout << "Max: " << doublePair.getMax() << std::endl;

    Pair<std::string> stringPair("Apple", "Banana");
    stringPair.show();
    std::cout << "Max: " << stringPair.getMax() << std::endl; // Lexicographical compare


    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Top (int): " << intStack.top() << std::endl;
    intStack.pop();
    std::cout << "After pop, top (int): " << intStack.top() << std::endl;

    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top (string): " << stringStack.top() << std::endl;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "Workshop 8!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime

    templateDemo();

    return 0;
}
