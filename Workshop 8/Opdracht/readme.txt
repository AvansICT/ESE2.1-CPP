SFML (Simple and Fast Multimedia Library) is een open-source en cross-platform C++-bibliotheek 
waarmee je eenvoudig grafische applicaties en games kunt maken.

SFML information
https://www.sfml-dev.org/
https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library 

Windows build steps
1.  Install cmake (tested with 4.4.3)
    https://github.com/Kitware/CMake/releases/download/v4.4.3/cmake-4.4.3-windows-x86_64.msi
2.  Download the SFML zip file from github
    https://github.com/SFML/SFML/archive/refs/tags/3.1.0.zip
    Extract the archive file to your directory of choice. 
    For this example it was extracted to "C:\SFML-3.1.0"
3.  Start Visual Studio and open a developer command prompt
    Visual studio menu: Tools -> Command Line -> Developer-Command Prompt
4.  Navigate to the unzipped folder
    cd C:\SFML-3.1.0
5.  Create a build folder and navigate to it
    mkdir build
    cd build
6.  Run cmake
    cmake ..
7.  Build debug version of SFML
    cmake --build . --config Debug
8.  Install debug version of SFML C:\SFML
    cmake --install . --config Debug --prefix C:\SFML\Debug
9.  Build Release version of SFML
    cmake --build . --config Release
10. Install Release version of SFML in C:\SFML
    cmake --install . --config Release --prefix C:\SFML\Release

    Ready for usage with Visual Studio!

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

5. Build SFML:
5a. Download the SFML zip file from github
wget https://github.com/SFML/SFML/archive/refs/tags/3.1.0.zip
5b. Unzip the file
unzip 3.1.0.zip
5c. navigate to the unzipped folder
cd SFML-3.1.0
5d. Create a build folder and navigate to it
mkdir build
    cd build
6.  Run cmake
    For SFML 3.1.0 you need to upgrade cmake to version 4.4.3, because the minimum required version
    sudo apt remove cmake
    (met "snap info cmak" kun je de versie van cmake zien die beschikbaar is via snap en 1562 is de versie die nodig is voor SFML 3.1.0)
    sudo snap install cmake --classic --revision=1562
    cmake ..
7.  Build debug version of SFML
    cmake --build . --config Debug
8.  Install debug version of SFML C:\SFML
    cmake --install . --config Debug --prefix C:\SFML\Debug
9.  Build Release version of SFML
    cmake --build . --config Release
10. Install Release version of SFML in C:\SFML
    cmake --install . --config Release --prefix C:\SFML\Release



Linux build steps for myApp

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

7. navigate to the unzipped folder
cd ESE2.1-CPP-main/Workshop\ 7/Workshop/tcpserver/

8. Create a build folder and navigate to it
mkdir build
cd build

9. Make sure g++ is used as C++ compiler
   (note: for c files use the gcc compiler must be used)
export CXX=/usr/bin/g++

11. Run cmake
cmake ..

12. Run make
make

13. Run the program
./tcpserver


8.  

mkdir build
cd build
cmake --build . --config Debug

cmake --install . --config Release --prefix ..\..\SFML



FLAC.lib
freetype.lib
harfbuzz.lib
libssh2.lib
mbedcrypto.lib
mbedtls.lib
mbedx509.lib
ogg.lib
sfml-audio-s.lib
sfml-graphics-s.lib
sfml-main.lib
sfml-network-s.lib
sfml-system-s.lib
sfml-window-s.lib
vorbis.lib
vorbisenc.lib
vorbisfile.lib
              17 File(s)     50.308.900 bytes
              
              
FLACd.lib
freetyped.lib
harfbuzzd.lib
libssh2.lib
mbedcryptod.lib
mbedtlsd.lib
mbedx509d.lib
oggd.lib
sfml-audio-s-d.lib
sfml-graphics-s-d.lib
sfml-main-d.lib
sfml-network-s-d.lib
sfml-system-s-d.lib
sfml-window-s-d.lib
vorbisd.lib
vorbisencd.lib
vorbisfiled.lib
608 bytes


