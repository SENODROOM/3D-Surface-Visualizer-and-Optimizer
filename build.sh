#!/bin/bash
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
cp /c/freeglut/bin/x64/freeglut.dll .
./optimizer.exe