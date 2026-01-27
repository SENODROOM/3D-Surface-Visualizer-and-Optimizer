@echo off
setlocal enabledelayedexpansion

echo =========================================
echo   3D Surface Optimizer - Build Script
echo =========================================
echo.

REM Check for CMake
where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found!
    echo Please install CMake and add it to PATH
    echo Download from: https://cmake.org/download/
    pause
    exit /b 1
)
echo [OK] CMake found

REM Check for compiler
where g++ >nul 2>&1
if errorlevel 1 (
    where cl >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] No C++ compiler found!
        echo Please install MinGW-w64 or Visual Studio
        pause
        exit /b 1
    ) else (
        set COMPILER=MSVC
        echo [OK] MSVC compiler found
    )
) else (
    set COMPILER=MINGW
    echo [OK] MinGW compiler found
)

echo.

REM Create build directory
if not exist build (
    echo Creating build directory...
    mkdir build
) else (
    echo Build directory exists
    set /p CLEAN="Clean build directory? (y/n): "
    if /i "!CLEAN!"=="y" (
        echo Cleaning build directory...
        rmdir /s /q build
        mkdir build
    )
)

cd build

REM Run CMake
echo.
echo Running CMake configuration...

if "%COMPILER%"=="MINGW" (
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
) else (
    cmake .. -DCMAKE_BUILD_TYPE=Release
)

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b 1
)
echo [OK] CMake configuration successful

REM Build
echo.
echo Compiling project...

if "%COMPILER%"=="MINGW" (
    mingw32-make
) else (
    cmake --build . --config Release
)

if errorlevel 1 (
    echo [ERROR] Compilation failed!
    pause
    exit /b 1
)
echo [OK] Compilation successful

REM Copy FreeGLUT DLL
echo.
echo Checking for freeglut.dll...

set DLL_FOUND=0

if exist C:\freeglut\bin\x64\freeglut.dll (
    copy /Y C:\freeglut\bin\x64\freeglut.dll . >nul 2>&1
    if not errorlevel 1 (
        echo [OK] Copied freeglut.dll from C:\freeglut\bin\x64\
        set DLL_FOUND=1
    )
)

if !DLL_FOUND!==0 (
    if exist C:\freeglut\bin\freeglut.dll (
        copy /Y C:\freeglut\bin\freeglut.dll . >nul 2>&1
        if not errorlevel 1 (
            echo [OK] Copied freeglut.dll from C:\freeglut\bin\
            set DLL_FOUND=1
        )
    )
)

if !DLL_FOUND!==0 (
    echo [WARNING] freeglut.dll not found!
    echo The program may not run without this file.
    echo Please copy freeglut.dll to the build directory manually.
)

REM Check executables
echo.
echo Checking build artifacts...

if exist optimizer.exe (
    echo [OK] optimizer.exe created
) else (
    echo [ERROR] optimizer.exe not found!
    pause
    exit /b 1
)

if exist optimizer_demo.exe (
    echo [OK] optimizer_demo.exe created
) else (
    echo [WARNING] optimizer_demo.exe not found
)

REM Success message
echo.
echo =========================================
echo   BUILD COMPLETE!
echo =========================================
echo.
echo Created executables:
echo   optimizer.exe       - Main program with equation GUI
echo   optimizer_demo.exe  - Original demo version
echo.
echo To run:
echo   optimizer.exe
echo.
echo Controls in 3D view:
echo   W/S - Rotate up/down
echo   A/D - Rotate left/right
echo   +/- - Zoom in/out
echo   R   - Reset view
echo   ESC - Exit
echo.
echo Press any key to run the program...
pause >nul

REM Run the program
optimizer.exe

echo.
echo Program ended. Press any key to close...
pause >nul