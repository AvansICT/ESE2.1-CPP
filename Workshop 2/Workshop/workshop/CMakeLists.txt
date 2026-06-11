cmake_minimum_required(VERSION 3.10)
project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(Workshop
    main.cpp
    robot.cpp
    ../../../Lib/log.cpp
)

# Add include directory for headers
target_include_directories(Workshop PRIVATE ../../../Lib)

# Explicitly link stdc++
target_link_libraries(Workshop PRIVATE stdc++)
