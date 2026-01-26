@echo off
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
if exist C:\freeglut\bin\x64\freeglut.dll (
    copy C:\freeglut\bin\x64\freeglut.dll . >nul 2>&1
) else (
    copy C:\freeglut\bin\freeglut.dll . >nul 2>&1
)
echo.
echo Running optimizer...
echo.
call optimizer.exe
echo.
echo Program ended. Press any key to close...
pause >nul