// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "log.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	std::cout << "myApp!\n";
	std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
	LogTargetOperatingSystem();
	LogTargetCompiler();
	LogTargetCxxStandard();
	LOG_DEBUG
	// Some fun with random numbers
	std::srand(static_cast<unsigned>(std::time(nullptr))); // init random

	// Fun "Hello World" greeting
	std::cout << "Hello, student! \n";

	// Random fun fact / tip / joke
	std::vector<std::string> funStuff = {
		"Did you know? C++ was created in 1985!",
		"Random tip: Take a short break every hour. ",
		"Fun fact: The first computer bug was an actual moth!",
		"Keep calm and code on! ",
		"Your lucky number today: " + std::to_string(std::rand() % 100 + 1)
	};

	int randomIndex = std::rand() % funStuff.size();
	std::cout << funStuff[randomIndex] << "\n";

	return 0;
}