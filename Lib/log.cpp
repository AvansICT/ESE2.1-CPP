#include <iostream>
#include <fstream>
#include <string>
#include "log.hpp"

#if defined(__linux__)
static bool IsWSL()
{
	std::ifstream file("/proc/version");
	std::string line;

	if (file.is_open())
	{
		std::getline(file, line);
		return line.find("Microsoft") != std::string::npos ||
			line.find("WSL") != std::string::npos;
	}

	return false;
}
#endif

void LogOperatingSystem(void)
{
#if defined(_WIN32) && defined(_WIN64)
	std::cout << "Running on Windows 64-bit" << std::endl;
#elif defined(_WIN32)
	std::cout << "Running on Windows 32-bit" << std::endl;
#elif defined(__APPLE__) || defined(__MACH__)
	std::cout << "Running on macOS" << std::endl;
#elif defined(__linux__)
	if (IsWSL())
	{
		std::cout << "Running on WSL (Windows Subsystem for Linux)" << std::endl;
	}
	else
	{
		std::cout << "Running on native Linux" << std::endl;
	}
#elif defined(__unix__)
	std::cout << "Running on Unix" << std::endl;
#elif defined(_POSIX_VERSION)
	std::cout << "Running on POSIX-compliant OS" << std::endl;
#else
	std::cout << "Unknown OS" << std::endl;
#endif
}

void LogCompiler(void)
{
#if defined(__clang__)
	std::cout << "Compiled with Clang version: " << __clang_version__ << std::endl;
#elif defined(__GNUC__) || defined(__GNUG__)
	std::cout << "Compiled with GCC version: " << __VERSION__ << " (" << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << ")" << std::endl;
#elif defined(_MSC_FULL_VER)
	std::cout << "Compiled with MSVC version: " << _MSC_FULL_VER << std::endl;
#else
	std::cout << "Unknown compiler" << std::endl;
#endif
}

void LogCxxStandard(void)
{
	std::cout << "C++ standard: ";

#if __cplusplus > 202302L
	std::cout << "C++26 or later";
#elif __cplusplus == 202302L
	std::cout << "C++23";
#elif __cplusplus == 202002L
	std::cout << "C++20";
#elif __cplusplus == 201703L
	std::cout << "C++17";
#elif __cplusplus == 201402L
	std::cout << "C++14";
#elif __cplusplus == 201103L
	std::cout << "C++11";
#elif __cplusplus == 199711L
	std::cout << "C++98/C++03";
#else
	std::cout << "pre C++11";
#endif
	std::cout << "(" << __cplusplus << ")" << std::endl;
}
