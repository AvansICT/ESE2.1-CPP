cmake_minimum_required(VERSION 3.10)
project(myApp LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BOOST (custom build in /usr/local)
set(BOOST_ROOT "/usr/local")
set(BOOST_INCLUDEDIR "/usr/local/include")
set(BOOST_LIBRARYDIR "/usr/local/lib")

find_package(Boost REQUIRED)

# Add the executable
add_executable(BoostVoorbeeld
    boostvoorbeeld.cpp
    ../../../Lib/log.cpp
)

# Add include directory for headers
target_include_directories(BoostVoorbeeld PRIVATE ../../../Lib ${Boost_INCLUDE_DIRS)

# Explicitly link stdc++
target_link_libraries(BoostVoorbeeld PRIVATE stdc++ ${Boost_LIBRARIES)
