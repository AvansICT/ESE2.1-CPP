# SFML
SFML (Simple and Fast Multimedia Library) is een open-source en cross-platform C++-bibliotheek 
waarmee je eenvoudig grafische applicaties en games kunt maken.

SFML information
https://www.sfml-dev.org/
https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library 

# Windows build steps
### 1.  Install cmake (tested with 4.4.3)
    https://github.com/Kitware/CMake/releases/download/v4.4.3/cmake-4.4.3-windows-x86_64.msi
### 2.  Download the SFML zip file from github
    https://github.com/SFML/SFML/archive/refs/tags/3.1.0.zip
    Extract the archive file to your directory of choice. 
    For this example it was extracted to "C:\SFML-3.1.0"
### 3.  Start Visual Studio and open a developer command prompt
    Visual studio menu: Tools -> Command Line -> Developer-Command Prompt
### 4.  Navigate to the unzipped folder
```bash
    cd C:\SFML-3.1.0
```
### 5.  Create a build folder and navigate to it
```bash
    mkdir build
    cd build
```
### 6.  Run cmake
```bash
    cmake ..
```
### 7.  Build debug version of SFML
```bash
    cmake --build . --config Debug
```
### 8.  Install debug version of SFML to C:\SFML (This path is hard-coded in the Workshop 8 projects.
    If you install SFML in a different location, update the project configuration accordingly)
```bash
    cmake --install . --config Debug --prefix C:\SFML\Debug
```
### 9.  Build Release version of SFML
```bash
    cmake --build . --config Release
```
### 10. Install Release version of SFML in to C:\SFML
    (This path is hard-coded in the Workshop 8 projects.
    If you install SFML in a different location, update the project configuration accordingly)
```bash
    cmake --install . --config Release --prefix C:\SFML\Release
```

Ready for usage with Visual Studio! You can open Workshop 8 projects sollution and compile, run an play the games!

### !!! When starting a new Visual Studio project, make sure to add the SFML include and lib directories to your project settings.!!!
### 1.  Make sure to add the include and lib directories of SFML to your project settings.
    Release build:
      Project settings -> C/C++ -> General -> Additional Include Directories -> C:\SFML\Release\include
      Project settings -> Linker -> General -> Additional Library Directories -> C:\SFML\Release\lib
    Debug build:
      Project settings -> C/C++ -> General -> Additional Include Directories -> C:\SFML\Debug\include
      Project settings -> Linker -> General -> Additional Library Directories -> C:\SFML\Debug\lib
### 2.  Make sure to add the SFML libraries to your project settings:
    Release build:
      Project settings -> Linker -> Input -> Additional Dependencies -> 
      FLAC.lib freetype.lib harfbuzz.lib libssh2.lib mbedcrypto.lib mbedtls.lib mbedx509.lib ogg.lib sfml-audio-s.lib sfml-graphics-s.lib sfml-main.lib sfml-network-s.lib sfml-system-s.lib sfml-window-s.lib vorbis.lib vorbisenc.lib vorbisfile.lib opengl32.lib winmm.lib gdi32.lib
    Debug build:
      Project settings -> Linker -> Input -> Additional Dependencies -> 
      FLACd.lib freetyped.lib harfbuzzd.lib libssh2.lib mbedcryptod.lib mbedtlsd.lib mbedx509d.lib oggd.lib sfml-audio-s-d.lib sfml-graphics-s-d.lib sfml-main-d.lib sfml-network-s-d.lib sfml-system-s-d.lib sfml-window-s-d.lib vorbisd.lib vorbisencd.lib vorbisfiled.lib opengl32.lib winmm.lib gdi32.lib
### 3.  Make sure to add the SFML_STATIC preprocessor definition to your project settings
     Project settings -> C/C++ -> Preprocessor -> Preprocessor Definitions -> SFML_STATIC

# Linux build steps (ubuntu)

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
su```do apt install unzip
```
### 5. Build SFML:
### 5a. make sure git is installed
```bash
sudo apt install git
```
### 5b. Check cmake version
    For SFML 3.1.0 you need to upgrade cmake to version 4.4.3, because the minimum required version
    check version of cmake with 
```bash
cmake --version
```
    if the version is lower than 4.4.3, you need to upgrade cmake to version 4.4.3, because the minimum required version
    check welke cmake versions beschikbaar zijn
```bash
snap info cmake
```
verwijder de huidige cmake versie en installeer de nieuwe versie (1562 is de versie die nodig is voor SFML 3.1.0)
```bash
sudo apt remove cmake
sudo snap install cmake --classic --revision=1562
```
### !!!Extra step for WSL (Windows Subsystem for Linux) add symbolic link to cmake in /usr/bin
```bash
sudo ln -sf /snap/cmake/current/bin/cmake /usr/bin/cmake
```
### 5c. install the required dependencies for SFML
```bash
sudo apt install \
    libx11-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype6-dev \
    libflac-dev \
    libogg-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libmbedtls-dev \
    libssh2-1-dev \
    libharfbuzz-dev
```
### 5d. Download the SFML zip file from github\
```bash
wget https://github.com/SFML/SFML/archive/refs/tags/3.1.0.zip
```
### 5e. Unzip the file
```bash
unzip 3.1.0.zip
```
### 5f. navigate to the unzipped folder
```bash
cd SFML-3.1.0
```
### 5g. Create a build folder and navigate to it
```bash
mkdir build
cd build
```
### 5h. Run cmake
```bash
    cmake ..
```
7.  Build SFML
```bash
cmake --build .
```
8.  Install SFML
```bash
sudo cmake --install . --prefix=/usr/local
```
### !!! Extra step for WSL install mesa-utils
```bash
sudo apt install mesa-utils
```
