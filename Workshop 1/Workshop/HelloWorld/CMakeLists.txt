cmake_minimum_required(VERSION 3.10)
project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(HelloWorld
    main.cpp
    rekenen.cpp
    ../../../Lib/log.cpp
)

# Add include directory for headers
target_include_directories(HelloWorld PRIVATE ../../../Lib)

# Explicitly link stdc++
target_link_libraries(HelloWorld PRIVATE stdc++)
