#include <iostream>
#include <string>
#include "log.hpp"

void typecastDemo(void)
{
    int a = 5;
    int b = 2;

    // Impliciete conversie (automatisch)
    double result1 = a / b;   // int / int = int (dus z = 2.0, niet 2.5!)
    std::cout << "Zonder cast: " << result1 << std::endl;

    // met C style cast
    double result2 = (double)a / b;
    std::cout << "met c cast: " << result2 << std::endl;

    // met C++ static cast (voorkeur)
    double result3 = static_cast<double>(a) / b;
    std::cout << "Met static_cast: " << result3 << std::endl;

	// Impliciete conversie (automatisch) int -> double
    double c = a;
    std::cout << "Impliciete conversie int -> double: " << c << std::endl;

	// Expliciete conversie double -> int (afkappen)
    double d = 3.99;
    int e = static_cast<int>(d);
	std::cout << "Expliciete conversie double -> int (afkappen): " << e << std::endl;

	// Pointer conversies (niet aanbevolen, gevaarlijk), compileerfout
    // int* p;
    // double* q;
    // p = q; //  niet toegestaan

	// Geoorloofde pointer conversie met reinterpret_cast, gevaarlijk
    int* p = nullptr;
    double* q = reinterpret_cast<double*>(p); // mag, maar gevaarlijk
    std::cout << "Pointer gecast met reinterpret_cast: " << q << std::endl;

    int w = 65; //ASCII - A
    char* pC = reinterpret_cast<char*>(&w);
    std::cout << *pC << std::endl;  // leest de eerste byte van int a

    class Base { public: virtual ~Base() {} };
    class Derived : public Base {};

    Base* base = new Derived();
    //Als base geen Derived is, geeft dynamic_cast een nullptr.
    Derived* der = dynamic_cast<Derived*>(base); // werkt veilig

    void* ptr = &a;
    // int* q = p; // Compileerfout, niet toegestaan
    int* m = static_cast<int*>(ptr); // veilig casten
    std::cout << "Pointer gecast: " << *m << std::endl;

    class Dier {
    public:
        virtual ~Dier() {}  // Polymorfisme vereist
    };

    class Hond : public Dier {
    public:
        void blaf() { std::cout << "Woef woef!" << std::endl; }
    };

    Dier* dier = new Hond();  // Eigenlijk een Hond, maar opgeslagen als Dier*

    // Downcast van Dier* -> Hond* met dynamic_cast
    Hond* hond = dynamic_cast<Hond*>(dier);

    if (hond) {
        std::cout << "Succesvolle cast!" << std::endl;
        hond->blaf();  // veilig te gebruiken
    }
    else {
        std::cout << "Cast mislukt!" << std::endl;
    }

    delete dier;

    int getal = 0x12345678;
    int* pGetal = &getal;

    // Cast int* naar char* om byte-per-byte te bekijken
    unsigned char* bytes = reinterpret_cast<unsigned char*>(pGetal);

    // Output (afhankelijk van je systeem-endianness)
    std::cout << "Bytes van getal (endianness zichtbaar):" << std::endl;
    for (int i = 0; i < sizeof(int); ++i) {
        std::cout << "Byte " << i << ": 0x"
            << std::hex << static_cast<int>(bytes[i]) << std::endl;
    }

}

void checkEndianness(void)
{
    uint32_t num = 0x12345678;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&num);

    std::cout << "Memory bytes: ";
    for (int i = 0; i < 4; ++i)
        std::cout << std::hex << static_cast<int>(ptr[i]) << " ";
    std::cout << std::dec << "\n";

    if (ptr[0] == 0x78)
        std::cout << "System is little-endian\n";
    else if (ptr[0] == 0x12)
        std::cout << "System is big-endian\n";
    else
        std::cout << "Unknown endianness\n";
}

void checkEndiannessModernWay(void) //Modern C++ Way (C++20)
{
    if constexpr (std::endian::native == std::endian::little)
        std::cout << "Little-endian\n";
    else if constexpr (std::endian::native == std::endian::big)
        std::cout << "Big-endian\n";
    else
        std::cout << "Mixed-endian (rare)\n";
}

void endiannessDemo(void)
{
    std::cout << "Endianness demo:\n";
    checkEndianness();
    checkEndiannessModernWay();
}

void declTypeDemo()
{
    int x = 42;
    double y = 3.14;

    // Compile-time type met decltype
    decltype(x) a = x;   // a is int
    decltype(y) b = y;   // b is double

    std::cout << "Compile-time types:" << std::endl;
    std::cout << "a is van type: " << typeid(a).name() << std::endl;
    std::cout << "b is van type: " << typeid(b).name() << std::endl;

    // Complexe expressie
    decltype(x + y) c = x + y; // c is double, want int+double = double
    std::cout << "c (x + y) is van type: " << typeid(c).name() << std::endl;

    // Type info op runtime
    auto d = c; // d krijgt type double via auto
    std::cout << "d (auto) runtime type: " << typeid(d).name() << std::endl;

}


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "Workshop 7!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    typecastDemo();
    endiannessDemo();
    declTypeDemo();

    return 0;
}
