-------------------------------------------------------------------------------
Windows build steps for jsonApp

1. Download the nlohmann json library
from https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip

2. Unzip the nlohmann json library to the folder Workshop 7
The structure should be like this:
Workshop 7
  |-- Workshop
	   |-- jsonApp
			|-- CMakeLists.txt
			|-- main.cpp
			|-- data.json
  |-- json-3.12.0
3. Check if the archive is unzipped correctly
Check if the file json-3.12.0/include/nlohmann/json.hpp exists
(the include directories are hardcoded in visual studio project file
 project properties -> C/C++ -> General -> Additional Include Directories)

4. build project with visual studio
-------------------------------------------------------------------------------
Linux build steps for jsonApp

1. Open terminal

2. Install gcc and g++ compilers
sudo apt install gcc
sudo apt install g++

3. Install cmake and make
sudo apt install cmake
sudo apt install make

4. Install unzip
sudo apt install unzip

5. Download the zip file from github
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip

6. Unzip the file
unzip main.zip

7. Download the nlohmann json library
wget https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip

8. Unzip the nlohmann json library to the folder Workshop 7
unzip v3.12.0.zip -d ESE2.1-CPP-main/Workshop\ 7/

10. Check if the archive is unzipped correctly
Check if the file json-3.12.0/include/nlohmann/json.hpp exists
(the include directories are hardcoded in CMakeLists.txt)

11. navigate to the unzipped folder
cd ESE2.1-CPP-main/Workshop\ 7/Workshop/jsonApp/

12. Create a build folder, copy json example file and navigate to it
mkdir build
cp data.json build/
cd build

13. Make sure g++ is used as C++ compiler
   (note: for c files use the gcc compiler must be used)
export CXX=/usr/bin/g++

14. Run cmake
cmake ..

15. Run make
make

16. Run the program
./jsonApp
