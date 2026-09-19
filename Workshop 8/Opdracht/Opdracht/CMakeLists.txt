cmake_minimum_required(VERSION 3.22)

project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SFML (custom static build in /usr/local)
set(SFML_DIR "/usr/local/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES ON)

# Find SFML
find_package(SFML 3 REQUIRED COMPONENTS
    Graphics
    Window
    System
)

# Add executable
add_executable(Opdracht
    main.cpp
    ../../../Lib/log.cpp
)

# Add include directory for own headers
target_include_directories(Opdracht PRIVATE
    ../../../Lib
)

# Link SFML
target_link_libraries(Opdracht PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
