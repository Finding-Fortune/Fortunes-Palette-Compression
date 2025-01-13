@echo off
REM Navigate to the build directory where the executable is located
cd build

REM Check if MainApp.exe exists
if not exist MainApp.exe (
    echo Error: MainApp.exe not found. Please build the project first.
    exit /b 1
)

REM Run the executable
MainApp.exe
