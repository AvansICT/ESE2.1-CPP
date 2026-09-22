
# Windows build steps for gunittest

The GoogleTest can be generated with Visual Studio for this project this was 
NOT done. The GoogleTest sources were downloaded and unzipped manually.
And these were included in the visual studio project. Look at the gtest filter
in the gunittest project for the included GoogleTest source files. And gtest-all.cc
was excluded from build.

### 1. Download the GoogleTest - Google Testing and Mocking Framework
from https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip

### 2. Unzip GoogleTest to the folder Workshop 8
The structure should be like this:
```bash
Workshop 8
  |-- Workshop
       |-- gunittest
            |-- CMakeLists.txt
            |-- gunittest.cpp
  |-- googletest-1.18.0
```
### 3. Check if the archive is unzipped correctly
Check if the file exists
(the include directories are hardcoded in visual studio project file
 project properties -> C/C++ -> General -> Additional Include Directories)
```bash
 /googletest-1.18.0/googletest/include/gtest/gtest.h 
```
### 4. build project with visual studio

# Linux build steps for gunittest

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
### 5 . Download the zip file from github
```bash
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip
```
### 6. Unzip the file
```bash
unzip main.zip
```
### 7. Download the GoogleTest - Google Testing and Mocking Framework
```bash
wget https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
```
### 8. Unzip the GoogleTest to the folder Workshop 8
```bash
unzip v1.18.0.zip -d ESE2.1-CPP-main/Workshop\ 8/
```
### 9. Check if the archive is unzipped correctly

Check if the file exists
(the include directories are hardcoded in CMakeLists.txt)
```bash
googletest-1.18.0/googletest/include/gtest/gtest.h
```
### 10. navigate to the unzipped folder
```bash
cd ESE2.1-CPP-main/Workshop\ 8/Workshop/gunittest/
```
### 11. Create a build folder and navigate to it
```bash
mkdir build
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
### 14  . Run make
```bash
make
```
### 15. Run the program
```bash
./gunittest
```
