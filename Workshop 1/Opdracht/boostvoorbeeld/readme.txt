Linux build steps

1. Open terminal

2. Install gcc and g++ compilers
sudo apt install gcc
sudo apt install g++

3. Install cmake and make
sudo apt install cmake
sudo apt install make

4. Install unzip
sudo apt install unzip

5. Build boost:
5a. Download the boost zip file
wget https://archives.boost.io/release/1.91.0/source/boost_1_91_0.tar.gz
5b.extract the archive
tar -xvzf boost_1_91_0.tar.gz
5c. navigate to it
cd boost_1_91_0
5d. run Bootstrap
sudo ./bootstrap.sh
5e. build and install (mocht je ergens anders installeren pas dan ook de CMakeLists.txt aan!)
sudo ./b2 install --prefix=/usr/local

6. Download the zip file from github
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip

7. Unzip the file
unzip main.zip

8. navigate to the unzipped folder
cd ESE2.1-CPP-main/Workshop\ 1/Opdracht/boostvoorbeeld/

9. Create a build folder and navigate to it
mkdir build
cd build

10. Make sure g++ is used as C++ compiler
   (note: for c files use the gcc compiler must be used)
export CXX=/usr/bin/g++

11. Run cmake
cmake ..

12. Run make
make

13. Run the program
./boostvoorbeeld
