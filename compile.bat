@echo off
REM Ensure we are in the root project directory

REM Create a build directory if it doesn't exist and compile app with ninja
if not exist build (
    mkdir build
    cd build
    cmake -G "Ninja" ^
    -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" 
    ..
    cd ..
)

REM Move into the build directory
cd build

REM Build the project using Ninja
ninja

REM Notify user that build is complete
echo Build complete!
