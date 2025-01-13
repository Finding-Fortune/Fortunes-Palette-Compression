# Minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Project Name
project(PaletteLib LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the library
add_library(PaletteLib STATIC
    src/palette.hpp
    src/palette.cpp
)

# Optionally, you can make it SHARED instead of STATIC
# add_library(PaletteLib SHARED src/palette.hpp)

# Specify the include directory for the library
target_include_directories(PaletteLib PUBLIC src)

# Add an executable for the main.cpp
add_executable(MainApp src/main.cpp)

# Link the library to the executable
target_link_libraries(MainApp PRIVATE PaletteLib)

# Optional: Add compiler options (use clang or gcc options here if required)
target_compile_options(PaletteLib PRIVATE -Wall -Wextra -pedantic)
target_compile_options(MainApp PRIVATE -Wall -Wextra -pedantic)
