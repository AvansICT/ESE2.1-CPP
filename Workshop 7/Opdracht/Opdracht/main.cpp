// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <print>    //C++23
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "log.hpp"

// Helper: print een vector van skills
static void printSkills(const std::vector<std::string>& skills) {
    for (const auto& s : skills)
        std::cout << s << " ";
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::print("Hello, Opdracht\n");    // C++23 feature

    struct User {
        std::string name;
        int age;
        std::vector<std::string> skills;
    };

    // users toevoegen
    std::vector<User> users = {
        {"Marcel", 42, {"C++", "Linux", "JSON"}},
        {"Anna", 29, {"Python", "Machine Learning"}},
        {"Tom", 35, {"C#", "Unity", "3D"}},
        {"Sophie", 33, {"Python", "C++"}}
    };

	//print alle users
    std::cout << "Alle gebruikers:\n";
    for (const auto& u : users) {
        std::cout << u.name << ", " << u.age << ", Skills: ";
        printSkills(u.skills);
    }
    std::cout << std::endl;

	//filteren op leeftijd > 30
    std::vector<User> olderThan30;
    std::copy_if(users.begin(), users.end(), std::back_inserter(olderThan30),
                 [](const User& u){ return u.age > 30; });

    std::cout << "Gebruikers ouder dan 30:\n";
    for (const auto& u : olderThan30) {
        std::cout << u.name << ", " << u.age << std::endl;
    }
    std::cout << std::endl;

	// sorteren op leeftijd
    std::sort(users.begin(), users.end(),
              [](const User& a, const User& b){ return a.age < b.age; });

    std::cout << "Gebruikers gesorteerd op leeftijd:\n";
    for (const auto& u : users)
        std::cout << u.name << ", " << u.age << std::endl;
    std::cout << std::endl;

	// sorteren op naam
    std::sort(users.begin(), users.end(),
              [](const User& a, const User& b){ return a.name < b.name; });

    std::cout << "Gebruikers gesorteerd op naam:\n";
    for (const auto& u : users)
        std::cout << u.name << std::endl;
    std::cout << std::endl;

	// skill anaylse
    std::map<std::string,int> skillCount;
    for (const auto& u : users) {
        for (const auto& s : u.skills) {
            skillCount[s]++;
        }
    }

    std::cout << "Aantal gebruikers per skill:\n";
    for (const auto& pair : skillCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;

	// zoeken naar specifieke gebruiker
    std::string zoekNaam = "Anna";
    auto it = std::find_if(users.begin(), users.end(),
                           [&](const User& u){ return u.name == zoekNaam; });
    if (it != users.end()) {
        std::cout << "Gevonden gebruiker: " << it->name << ", leeftijd " << it->age << std::endl;
    } else {
        std::cout << "Gebruiker " << zoekNaam << " niet gevonden!" << std::endl;
    }

    return 0;
}
