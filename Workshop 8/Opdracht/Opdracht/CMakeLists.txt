cmake_minimum_required(VERSION 3.10)
project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML (custom build in /usr/local)
set(SFML_ROOT "/usr/local")
set(SFML_DIR "/usr/local/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Add the executable
add_executable(SFMLVoorbeeld
    sfmlvoorbeeld.cpp
    ../../../Lib/log.cpp
)

# Add include directory for headers
target_include_directories(SFMLVoorbeeld PRIVATE
    ../../../Lib
)

# Link SFML
target_link_libraries(SFMLVoorbeeld PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)