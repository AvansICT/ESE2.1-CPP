// Example from: https://web.archive.org/web/20190228003127/https://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include "chronotimer.hpp"

std::string fetchDataFromDB(const std::string& recvdData) {
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//Do stuff like creating DB Connection and fetching Data
	return "DB_" + recvdData;
}

std::string fetchDataFromFile(const std::string& recvdData) {
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//Do stuff like fetching Data File
	return "File_" + recvdData;
}

int main(int argc, char* argv[]) {
	std::cout << "AsyncExample!\n";
	std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime

	// Get Start Time
	ChronoTimer t1;
	t1.startTimerSystemClock();

	auto resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");

	//Fetch Data from File
	std::string fileData = fetchDataFromFile("Data");

	//Fetch Data from DB
	// Will block till data is available in future<std::string> object.
	std::string dbData = resultFromDB.get();

	// Get End Time
	t1.stopTimerSystemClock();

	std::cout << "Total Time Taken = " << t1.elapsedTimeSystemClock() << " Seconds" << std::endl;

	//Combine The Data
	std::string data = dbData + " :: " + fileData;

	//Printing the combined Data
	std::cout << "Data = " << data << std::endl;
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
	__debugbreak(); // hardcoded breakpoint for debug build only
#endif
	return 0;
}
