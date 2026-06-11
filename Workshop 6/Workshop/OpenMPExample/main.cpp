#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "clocktimer.hpp"

using namespace std;

//#define LOG_NUMBERS

void selectionSortParallel(vector<int>& A);
void selectionSortSerial(vector<int>& A);
void verify(vector<int>& A);

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	std::cout << "OpenMPExample\n";
	std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime

	int number;
	clocktimer t1;

	cout << "Enter number of items to sort: " << endl;
	cin >> number;

	vector<int> v(number);

	static uniform_int_distribution<int> range(0, 100); // Define range
	static default_random_engine randomizer; // Randomizer
	generate(v.begin(), v.end(), []() { return range(randomizer); });

	// Parallel
	t1.startTimer();
	selectionSortParallel(v);
	t1.stopTimer();
	double cpu_time_used_parallel = t1.elapsedTime();

	// Serial
	vector<int> v2(v);
	t1.startTimer();
	selectionSortSerial(v2);
	t1.stopTimer();
	double cpu_time_used_serial = t1.elapsedTime();

	// Verify if the algorithm works as advised
	verify(v);
	verify(v2);

	cout << "Time taken for sort parallel: " << cpu_time_used_parallel << " vs serial: " << cpu_time_used_serial << endl;
	std::cout << "Output serial: " << std::endl;
#ifdef LOG_NUMBERS
	// log with foreach and lambda
	int idx = 0;
	std::for_each(v2.begin(), v2.end(), [&](long long val) {
		std::cout << "[" << idx++ << "]=" << val << " ";
		});
	cout << endl;
	cout << "Output Parallel: " << endl;
	// range - based for with index
	idx = 0;
	for (const auto& val : v) {
		std::cout << "[" << idx++ << "]=" << val << " ";
	}
	cout << endl;
#endif
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
	__debugbreak(); // hardcoded breakpoint for debug build only
#endif

	return 0;
}
void selectionSortSerial(vector<int>& A) {
	for (std::vector<int>::iterator it = A.begin(); it != A.end(); ++it) {
		iter_swap(it, min_element(it, A.end()));
	}
}

void selectionSortParallel(vector<int>& A) {

	// Structure for enabling reduction on the index of elements
	struct Compare { int val; int index; };

	int iCPU = omp_get_num_procs(); // Get the number of processors in this system
	cout << "Using number of cores: " << iCPU << endl;

	omp_set_num_threads(iCPU); // Now set the number of threads

	for (int startpos = 0; startpos < A.size(); startpos++) {
		// Declare the structure required for reduction
		struct Compare smin;
		// Initialize the variables
		smin.val = A[startpos];
		smin.index = startpos;

		// Parallel for loop 
#pragma omp parallel for 
		for (int i = startpos + 1; i < A.size(); ++i) {
			if (A[i] < smin.val) {
#pragma omp critical // Needed because VS doesn't support reduction
				if (A[i] < smin.val) {
					smin.val = A[i];
					smin.index = i;
				}
			}
		}

		std::swap(A[startpos], A[smin.index]);
	}
}

// Verification function
void verify(vector<int>& A) {
	int failcount = 0;
	for (int iter = 0; iter < A.size() - 1; iter++) {
		if (A[iter] > A[iter + 1]) {
			failcount++;
		}
	}
	std::cout << "Fail count: " << failcount << endl;
}


