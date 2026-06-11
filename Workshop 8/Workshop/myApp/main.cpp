#include <iostream>
#include <vector>
#include "log.hpp"
#include "mymath.hpp"

#define N1 12
#define N2 4

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // simple basic app used for unit tests
    std::cout << "myApp uses myMath!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogOperatingSystem();
    LogCompiler();
    LogCxxStandard();
	// use the functions from myapp
    std::cout << "add result:" << myMath::add(N1, N2) << std::endl;
    std::cout << "sub result:" << myMath::subtract(N1, N2) << std::endl;
    std::cout << "mul result:" << myMath::multiply(N1, N2) << std::endl;
    std::cout << "div result:" << myMath::divide(N1, N2) << std::endl;
    std::cout << "mod result:" << myMath::modulus(N1, N2) << std::endl;
    
    myMath::MathFunctions M;
    // Use the MathFunctions class 
    std::cout << "add class result:" << M.add(N1, N2) << std::endl;
    std::cout << "sub class result:" << M.subtract(N1, N2) << std::endl;
    std::cout << "mul class result:" << M.multiply(N1, N2) << std::endl;
    std::cout << "div class result:" << M.divide(N1, N2) << std::endl;
    std::cout << "mod class result:" << M.modulus(N1, N2) << std::endl;

    return 0;
}
