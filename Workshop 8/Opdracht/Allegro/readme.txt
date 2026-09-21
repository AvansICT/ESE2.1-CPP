Opdracht hello universebuild with allegro5-5.2.11.3 https://github.com/liballeg/allegro5/tags

Allegro is ook een open-source en cross-platform C++-bibliotheek 
waarmee je eenvoudig grafische applicaties en games kunt maken. 

Allegro information
https://www.allegro.cc/
https://en.wikipedia.org/wiki/Allegro_(game_engine)

Windows build steps
1.  Install cmake (tested with 4.4.3)
    https://github.com/Kitware/CMake/releases/download/v4.4.3/cmake-4.4.3-windows-x86_64.msi
2.  Download the SFML zip file from github
    https://github.com/liballeg/allegro5/archive/refs/tags/5.2.11.3.zip
    Extract the archive file to your directory of choice. 
    For this example it was extracted to "C:\allegro5-5.2.11.3"
    (Extract gives an error: cannot create symlink, a required privilege is not held by the client,allegro5-5.2.11.3\README.md
    but the files are extracted correctly)
3.  Start Visual Studio and open a developer command prompt
    Visual studio menu: Tools -> Command Line -> Developer-Command Prompt4.  Navigate to the unzipped folder
    cd C:\allegro5-5.2.11.3
5.  Create a build folder and navigate to it
    mkdir build
    cd build
6.  Run cmake
    cmake -S .. -B . -DSHARED=OFF -DWANT_D3D=OFF -DWANT_DSOUND=OFF
    cmake -S .. -B . -G "Visual Studio 18 2026" -A x64 -DSHARED=OFF -DWANT_D3D=OFF -DWANT_DSOUND=OFF -DCMAKE_CONFIGURATION_TYPES="Debug;Release;RelWithDebInfo"
7.  Build debug version of Allegro
    cmake --build . --config Debug
    8.  Install debug version of Allegro to C:\Allegro (This path is hard-coded in the Workshop 8 Allegro project.
    If you install Allegro in a different location, update the project configuration accordingly)
    cmake --install . --config Debug --prefix C:\Allegro\Debug
9.  Build Release version of SFML
    cmake --build . --config Release
10. Install Release version of Allegro in to C:\Allegro
    (This path is hard-coded in the Workshop 8 projects.
    If you install Allegro in a different location, update the project configuration accordingly)
    cmake --install . --config Release --prefix C:\Allegro\Release

Build Allegro project for a demo!

Linux build steps
Note this is tested after FSML build steps, might be steps needed from FMSL?
1. Open terminal

2. Install gcc and g++ compilers
sudo apt install gcc
sudo apt install g++

3. Install cmake and make
sudo apt install cmake
sudo apt install make

4. Install unzip
sudo apt install unzip

5. Build Allegro
5a Download the Allegro zip file from github
    wget https://github.com/liballeg/allegro5/archive/refs/tags/5.2.11.3.zip
5e. Unzip the file
    unzip 5.2.11.3.zip
5f. navigate to the unzipped folder
    cd allegro5-5.2.11.3
5g. Create a build folder and navigate to it
    mkdir build
cd build
5h. Run cmake
    cmake -S .. -B . -DSHARED=OFF
5i. Build Allegro
    cmake --build . -j$(nproc)
5j. Install Allegro
    sudo cmake --install . --prefix=/usr/local

6. Build Allegro project for a demo!
6a. Download the zip file from github
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip
6b. Unzip the file
unzip main.zip
6c. navigate to the unzipped folder
cd ESE2.1-CPP-main/Workshop\ 8/Opdracht/Allegro/
6d. Create a build folder and navigate to it
mkdir build
cd build
6e. Run cmake
cmake ..
6f. Run make
make
6e. Run the program
./Opdracht
