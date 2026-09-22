# Windows build steps for jsonApp

### 1. Download the nlohmann json library
from https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip

### 2. Unzip the nlohmann json library to the folder Workshop 7
The structure should be like this:
```bash
Workshop 7
  |-- Workshop
       |-- jsonApp
            |-- CMakeLists.txt
            |-- main.cpp
            |-- data.json
  |-- json-3.12.0
```
### 3. Check if the archive is unzipped correctly
Check if the file exists
(the include directories are hardcoded in visual studio project file
 project properties -> C/C++ -> General -> Additional Include Directories)
```bash
json-3.12.0/include/nlohmann/json.hpp 
```
### 4. build project with visual studio
# Linux build steps for jsonApp
### 1. Open terminal

### 2. Install gcc and g++ compilers
```bash
sudo apt install gcc
sudo apt install g++
```
### 3. Install cmake and make
```bash
sudo apt install cmake
sudo apt install make
```
### 4. Install unzip
```bash
sudo apt install unzip
```
### 5. Download the zip file from github
```bash
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip
```
### 6. Unzip the file
```bash
unzip main.zip
```
### 7. Download the nlohmann json library
```bash
wget https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip
```
### 8. Unzip the nlohmann json library to the folder Workshop 7
```bash
unzip v3.12.0.zip -d ESE2.1-CPP-main/Workshop\ 7/
```
### 9. Check if the archive is unzipped correctly
Check if the file exists (the include directories are hardcoded in CMakeLists.txt)
```bash
json-3.12.0/include/nlohmann/json.hpp 
```
### 10. navigate to the unzipped folder
```bash
cd ESE2.1-CPP-main/Workshop\ 7/Workshop/jsonApp/
```
### 11. Create a build folder, copy json example file and navigate to it
```bash
mkdir build
cp data.json build/
cd build
```
### 12. Make sure g++ is used as C++ compiler
   (note: for c files use the gcc compiler must be used)
```bash
export CXX=/usr/bin/g++
```
### 13. Run cmake
```bash
cmake ..
```
### 14. Run make
```bash
make
```
### 15. Run the program
```bash
./jsonApp
```
