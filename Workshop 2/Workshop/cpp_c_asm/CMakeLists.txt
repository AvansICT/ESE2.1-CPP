cmake_minimum_required(VERSION 3.10)
project(cpp_c_asm LANGUAGES C CXX ASM)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Require C11
set(CMAKE_C_STANDARD 11)

# FORCE C compiler for this file
set_source_files_properties(../../../Lib/clog.c crc.c PROPERTIES LANGUAGE C)

# Add the executable
add_executable(cpp_c_asm_x64
    main.cpp
    swap.cpp
    crc.c
    bitdemo.cpp
    ../../../Lib/log.cpp
    ../../../Lib/clog.c
    calcx64.S
)

# Add include directory for headers
target_include_directories(cpp_c_asm_x64 PRIVATE ../../../Lib)

target_compile_options(cpp_c_asm_x64 PRIVATE
    -Wall
    -Wextra
    -pedantic
)

# Explicitly link stdc++
target_link_libraries(cpp_c_asm_x64 PRIVATE stdc++)


# Add the executable
add_executable(cpp_c_asm_x86
    main.cpp
    swap.cpp
    crc.c
    bitdemo.cpp
    ../../../Lib/log.cpp
    ../../../Lib/clog.c
    calcx86.S
)

# Add include directory for headers
target_include_directories(cpp_c_asm_x86 PRIVATE ../../../Lib)

target_compile_options(cpp_c_asm_x86 PRIVATE -m32
    -Wall
    -Wextra
    -pedantic
)

# Explicitly link stdc++
target_link_libraries(cpp_c_asm_x86 PRIVATE -m32 stdc++)