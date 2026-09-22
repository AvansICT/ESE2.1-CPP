# Allegro
Opdracht hello universebuild with allegro5-5.2.11.3 https://github.com/liballeg/allegro5/tags

Allegro is ook een open-source en cross-platform C++-bibliotheek 
waarmee je eenvoudig grafische applicaties en games kunt maken.

Ga eerst aan de slag met SFML, vervolgens kun je hiermee aan de slag.
Allegro is een alternatief voor SFML, en heeft een andere API en andere functies.

De hello universe opdracht is ook beschikbaar in Allegro, en kan worden gebouwd met de Allegro.

Allegro information
https://www.allegro.cc/
https://en.wikipedia.org/wiki/Allegro_(game_engine)

# Windows build steps
### 1.  Install cmake (tested with 4.4.3)
```bash
    https://github.com/Kitware/CMake/releases/download/v4.4.3/cmake-4.4.3-windows-x86_64.msi
```
### 2.  Download the SFML zip file from github
```bash
    https://github.com/liballeg/allegro5/archive/refs/tags/5.2.11.3.zip
```
    Extract the archive file to your directory of choice.     For this example it was extracted to
```bash
"C:\allegro5-5.2.11.3"
```
    (Extract gives an error: cannot create symlink, a required privilege is not held by the client,allegro5-5.2.11.3\README.md
    but the files are extracted correctly)

### 3.  Start Visual Studio and open a developer command prompt
```bash
    Visual studio menu: Tools -> Command Line -> Developer-Command Prompt4.  
```
    Navigate to the unzipped folder
```bash
    cd C:\allegro5-5.2.11.3
```
### 4.  Create a build folder and navigate to it
```bash
    mkdir build
    cd build
```
### 5.  Run cmake
```bash
    cmake -S .. -B . -DSHARED=OFF -DWANT_D3D=OFF -DWANT_DSOUND=OFF
    cmake -S .. -B . -G "Visual Studio 18 2026" -A x64 -DSHARED=OFF -DWANT_D3D=OFF -DWANT_DSOUND=OFF -DCMAKE_CONFIGURATION_TYPES="Debug;Release;RelWithDebInfo"
```
### 6.  Build debug version of Allegro
```bash
    cmake --build . --config Debug
```
### 7.  Install debug version of Allegro to C:\Allegro 
    (This path is hard-coded in the Workshop 8 Allegro project.
    If you install Allegro in a different location, update the project configuration accordingly)
```bash
    cmake --install . --config Debug --prefix C:\Allegro\Debug
```
### 8.  Build Release version of Allegro
```bash
    cmake --build . --config Release
```
### 9.  Install Release version of Allegro in to C:\Allegro
    (This path is hard-coded in the Workshop 8 projects.
    If you install Allegro in a different location, update the project configuration accordingly)
```bash
    cmake --install . --config Release --prefix C:\Allegro\Release
```
Build Allegro project for a demo!

# Linux build steps
Note this is tested after FSML build steps, might be steps needed from FMSL?
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
### 5. Build Allegro
### 5a. Download the Allegro zip file from github
```bash
    wget https://github.com/liballeg/allegro5/archive/refs/tags/5.2.11.3.zip
```
### 5b. Unzip the file
```bash
    unzip 5.2.11.3.zip
```
### 5c. navigate to the unzipped folder
```bash
    cd allegro5-5.2.11.3
```
### 5d. Create a build folder and navigate to it
```bash
    mkdir build
    cd build
```
### 5e. Run cmake
```bash
    cmake -S .. -B . -DSHARED=OFF
```
### 5f. Build Allegro
```bash
    cmake --build . -j$(nproc)
```
### 5g. Install Allegro
```bash
    sudo cmake --install . --prefix=/usr/local
```
### 6. Build Allegro project for a demo!
### 6a. Download the zip file from github
```bash
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip
```
### 6b. Unzip the file
```bash
unzip main.zip
```
### 6c. navigate to the unzipped folder
```bash
cd ESE2.1-CPP-main/Workshop\ 8/Opdracht/Allegro/
```
### 6d. Create a build folder and navigate to it
```bash
mkdir build
cd build
```
### 6e. Run cmake
```bash
cmake ..
```
### 6f. Run make
```bash
make
```
### 6g. Run the program
```bash
./Opdracht
```

Veel plezier met Allegro en de hello universe demo!
