# Linux build steps

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
### 5. Build boost:
### 5a. Download the boost zip file
```bash
wget https://archives.boost.io/release/1.92.0/source/boost_1_92_0.tar.gz
```
### 5b. Extract the archive
```bash
tar -xvzf boost_1_92_0.tar.gz
```
### 5c. Navigate to it
```bash
cd boost_1_92_0
```
### 5d. Run Bootstrap
```bash
sudo ./bootstrap.sh
```
### 5e. Build and install (mocht je ergens anders installeren pas dan ook de CMakeLists.txt aan!)
```bash
sudo ./b2 install --prefix=/usr/local
```
### 6. Download the zip file from github
```bash
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip

### 7. Unzip the file
```bash
unzip main.zip
```
### 8. navigate to the unzipped folder
```bash
cd ESE2.1-CPP-main/Workshop\ 8/Workshop/boostunittest/
```
### 9. Create a build folder and navigate to it
```bash
mkdir build
cd build
```
### 10. Make sure g++ is used as C++ compiler
###    (note: for c files use the gcc compiler must be used)
```bash
export CXX=/usr/bin/g++
```
### 11. Run cmake
```bash
cmake ..
```
### 12. Run make
```bash
make
```
### 13. Run the program
```bash
./boostvoorbeeld
```
