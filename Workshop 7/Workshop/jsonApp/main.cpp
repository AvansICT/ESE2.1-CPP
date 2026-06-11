#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "log.hpp"

using json = nlohmann::json;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "jsonApp!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogTargetOperatingSystem();
    LogTargetCompiler();
	LogTargetCxxStandard();
	std::cout << "nlohmann::json version: " << NLOHMANN_JSON_VERSION_MAJOR << "." << NLOHMANN_JSON_VERSION_MINOR << "." << NLOHMANN_JSON_VERSION_PATCH << std::endl;

    // JSON uit bestand inlezen
    std::ifstream file("data.json");
    if (!file.is_open()) {
        std::cerr << "Kon data.json niet openen!" << std::endl;
        return 1;
    }

    json j;
    file >> j;

    // Data gebruiken
    std::cout << "Naam: " << j["name"] << std::endl;
    std::cout << "Leeftijd: " << j["age"] << std::endl;
    std::cout << "Skills:" << std::endl;
    for (auto& skill : j["skills"]) {
        std::cout << " - " << skill << std::endl;
    }

    // Data aanpassen
    j["age"] = j["age"].get<int>() + 1;
    j["skills"].push_back("JSON");

    // Nieuwe key toevoegen
    j["active"] = true;

    // Opslaan in nieuw bestand
    std::ofstream out("data_out.json");
    out << std::setw(4) << j << std::endl;

    std::cout << "Nieuwe data is weggeschreven naar data_out.json" << std::endl;

    return 0;
}
