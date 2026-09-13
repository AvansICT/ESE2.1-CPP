cmake_minimum_required(VERSION 3.10)
project(gunittest LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(gunittest
    gunittest.cpp
    ../myApp/mymath.cpp
    ../../../Lib/log.cpp
    ../../googletest-1.18.0/googletest/src/gtest.cc
    ../../googletest-1.18.0/googletest/src/gtest_main.cc
    ../../googletest-1.18.0/googletest/src/gtest-assertion-result.cc
    ../../googletest-1.18.0/googletest/src/gtest-death-test.cc
    ../../googletest-1.18.0/googletest/src/gtest-filepath.cc
    ../../googletest-1.18.0/googletest/src/gtest-matchers.cc
    ../../googletest-1.18.0/googletest/src/gtest-port.cc
    ../../googletest-1.18.0/googletest/src/gtest-printers.cc
    ../../googletest-1.18.0/googletest/src/gtest-test-part.cc
    ../../googletest-1.18.0/googletest/src/gtest-typed-test.cc
)

# Add include directory for headers
target_include_directories(gunittest
    PRIVATE
    ../../../Lib
    ../myApp
    ../../googletest-1.18.0/googletest
    ../../googletest-1.18.0/googletest/include
)

# Explicitly link stdc++
target_link_libraries(gunittest PRIVATE stdc++)
