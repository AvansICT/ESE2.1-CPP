make_minimum_required(VERSION 3.22)

project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Allegro
set(Allegro5_DIR "/usr/local/lib/cmake/Allegro5")

# Find Allegro
find_package(Allegro5 REQUIRED)

# Add executable
add_executable(Opdracht
    main.cpp
    ../../../Lib/log.cpp
)

# Add include directory for own headers
target_include_directories(Opdracht PRIVATE
    ../../../Lib
)

# Link Allegro
target_link_libraries(Opdracht PRIVATE
    Allegro::Allegro
    Allegro::Primitives
)