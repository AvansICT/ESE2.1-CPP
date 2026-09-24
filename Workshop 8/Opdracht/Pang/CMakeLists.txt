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
add_executable(Pang
    main.cpp
    ../../../Lib/log.cpp
)

# Add include directory for own headers
target_include_directories(Pang PRIVATE
    ../../../Lib
)

# Link SFML
target_link_libraries(Pang PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Copy assets next to executable after build
add_custom_command(TARGET Pang POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/../assets"
        "$<TARGET_FILE_DIR:Pang>"
)
