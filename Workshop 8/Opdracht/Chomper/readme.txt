Windows build steps

First make sure you have build and installed SFML, refer to readme.txt in the main solution for instructions

Tips when starting a new project:
1.  Make sure to add the include and lib directories of SFML to your project settings.
    Release build:
      Project settings -> C/C++ -> General -> Additional Include Directories -> C:\SFML\Release\include
      Project settings -> Linker -> General -> Additional Library Directories -> C:\SFML\Release\lib
    Debug build:
      Project settings -> C/C++ -> General -> Additional Include Directories -> C:\SFML\Debug\include
      Project settings -> Linker -> General -> Additional Library Directories -> C:\SFML\Debug\lib
2.  Make sure to add the SFML libraries to your project settings:
    Release build:
      Project settings -> Linker -> Input -> Additional Dependencies -> 
      FLAC.lib freetype.lib harfbuzz.lib libssh2.lib mbedcrypto.lib mbedtls.lib mbedx509.lib ogg.lib sfml-audio-s.lib sfml-graphics-s.lib sfml-main.lib sfml-network-s.lib sfml-system-s.lib sfml-window-s.lib vorbis.lib vorbisenc.lib vorbisfile.lib opengl32.lib winmm.lib gdi32.lib
    Debug build:
      Project settings -> Linker -> Input -> Additional Dependencies -> 
      FLACd.lib freetyped.lib harfbuzzd.lib libssh2.lib mbedcryptod.lib mbedtlsd.lib mbedx509d.lib oggd.lib sfml-audio-s-d.lib sfml-graphics-s-d.lib sfml-main-d.lib sfml-network-s-d.lib sfml-system-s-d.lib sfml-window-s-d.lib vorbisd.lib vorbisencd.lib vorbisfiled.lib opengl32.lib winmm.lib gdi32.lib
3.  Make sure to add the SFML_STATIC preprocessor definition to your   
      Project settings -> C/C++ -> Preprocessor -> Preprocessor Definitions -> SFML_STATIC


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

5. Download the zip file from github
wget https://github.com/AvansICT/ESE2.1-CPP/archive/refs/heads/main.zip

6. Unzip the file
unzip main.zip

7. navigate to the unzipped folder
cd ESE2.1-CPP-main/Workshop\ 2/Workshop/workshop/

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
./Workshop
