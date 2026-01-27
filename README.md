# 3D Surface Optimizer with Equation Input GUI

A powerful C++ application that visualizes mathematical surfaces in 3D and finds their minimum points using optimization algorithms with an interactive equation parser GUI.

## 🎯 Features

### ✨ Interactive Equation Parser
- **Type any mathematical equation** directly into the GUI
- **Real-time validation** with helpful error messages
- **Visual feedback** and cursor navigation
- **Easy configuration** of all parameters
- **Seamless 3D visualization**

### 📊 3D Visualization
- **OpenGL-powered** smooth rendering
- **Interactive camera** controls
- **Optimization path** visualization
- **Color-coded** start/end points

### 🔧 Optimization
- **Gradient descent** algorithm
- **Configurable** learning rate
- **Path tracking** for visualization
- **Convergence detection**

## 🚀 Quick Start

### Prerequisites

#### Windows
- **MinGW-w64** or Visual Studio with C++17 support
- **CMake** 3.10 or higher
- **FreeGLUT** installed at `C:/freeglut/` or custom path

#### Linux
```bash
sudo apt-get install build-essential cmake freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

#### macOS
```bash
brew install cmake freeglut
```

### Building

#### Windows (MinGW)
```batch
# Double-click run.bat or in terminal:
run.bat
```

#### Linux/macOS
```bash
chmod +x build.sh
./build.sh
cd build
./optimizer
```

#### Manual Build (All Platforms)
```bash
mkdir build
cd build
cmake ..
cmake --build .
./optimizer  # or optimizer.exe on Windows
```

## 📖 User Guide

### 1. Equation Input Screen

**Enter your equation** using variables `x` and `y`:

**Examples:**
```
Simple:
  x^2 + y^2              → Paraboloid (bowl shape)
  x^2 - y^2              → Saddle surface
  sin(x) * cos(y)        → Wave pattern

Advanced:
  exp(-(x^2 + y^2))      → Gaussian bell curve
  sqrt(x^2 + y^2)        → Cone
  sin(sqrt(x^2 + y^2))   → Ripple pattern
  (1-x)^2 + 100*(y-x^2)^2 → Rosenbrock function
```

**Supported Operations:**
- Basic: `+`, `-`, `*`, `/`, `^`, `%`
- Functions: `sin`, `cos`, `tan`, `exp`, `log`, `sqrt`, `abs`
- Binary: `pow(x,y)`, `min(x,y)`, `max(x,y)`

**Controls:**
- Type to enter equation
- Arrow keys to move cursor
- `ENTER` to validate and continue
- `ESC` to exit

### 2. Configuration Screen

**Parameters to configure:**

| Parameter | Description | Recommended Range |
|-----------|-------------|-------------------|
| Run Optimization | Enable gradient descent (y/n) | y or n |
| Start X | X coordinate of starting point | Within X bounds |
| Start Y | Y coordinate of starting point | Within Y bounds |
| Learning Rate | Step size for optimization | 0.001 - 0.1 |
| X Min/Max | Bounds for X axis | -10 to 10 (typical) |
| Y Min/Max | Bounds for Y axis | -10 to 10 (typical) |
| Resolution | Mesh detail (10-200) | 50 (balanced) |

**Controls:**
- `UP/DOWN` arrows to navigate fields
- Type to edit current field
- `ENTER` to confirm and move to next
- `ESC` to go back to equation input

### 3. 3D Visualization

**Camera Controls:**
- `W/S` - Rotate up/down
- `A/D` - Rotate left/right  
- `+/-` - Zoom in/out
- `R` - Reset view
- `ESC` - Exit

**Visual Legend:**
- 🔵 **Blue surface** - Your 3D equation
- 🟢 **Green sphere** - Optimization start point
- 🔴 **Red sphere** - Found minimum point
- 🔴 **Red line** - Optimization path

## 🛠️ Debugging Guide

### Common Issues and Fixes

#### 1. Missing GUIManager.cpp Error

**Symptom:** Compilation fails with "GUIManager.cpp not found"

**Fix:**
The `GUIManager.cpp` file has been created in the improved version. Ensure all files are present:
```bash
ls -l *.cpp *.h src/*.cpp include/*.h
```

**Required files:**
- `GUIManager.cpp` (main implementation)
- `GUIManager.h` (header)
- `EquationParser.cpp` and `.h`
- All files in `src/` and `include/`

#### 2. FreeGLUT Library Not Found

**Symptom:** `fatal error: GL/glut.h: No such file or directory`

**Windows Fix:**
1. Download FreeGLUT from http://freeglut.sourceforge.net/
2. Extract to `C:\freeglut\`
3. Or update CMakeLists.txt with your path:
   ```cmake
   set(FREEGLUT_DIR "D:/path/to/freeglut")
   ```

**Linux Fix:**
```bash
sudo apt-get install freeglut3-dev
```

**macOS Fix:**
```bash
brew install freeglut
```

#### 3. freeglut.dll Not Found (Windows)

**Symptom:** Program won't run, missing DLL error

**Fix:**
```bash
# Copy DLL to build directory
copy C:\freeglut\bin\x64\freeglut.dll build\
# Or add freeglut\bin to PATH
```

#### 4. Equation Validation Fails

**Symptom:** "Invalid equation" or syntax error

**Common Issues:**
- ❌ `2x` → ✅ `2*x` (use explicit multiplication)
- ❌ `sin x` → ✅ `sin(x)` (functions need parentheses)
- ❌ `x**2` → ✅ `x^2` or `pow(x,2)` (use ^ for power)
- ❌ `(x+y` → ✅ `(x+y)` (balance parentheses)

#### 5. Optimization Not Converging

**Symptom:** Optimization runs but doesn't find minimum

**Fixes:**
- **Reduce learning rate**: Try 10× smaller (e.g., 0.01 → 0.001)
- **Change starting point**: Try different (startX, startY)
- **Increase bounds**: Make sure minimum is within visualization bounds
- **Some surfaces have no minimum**: Saddle surfaces, planes, etc.

#### 6. Compilation Errors

**C++17 Not Supported:**
```bash
# Update compiler
# Windows: Install latest MinGW-w64
# Linux: sudo apt-get install g++-9
# macOS: brew install gcc
```

**Linking Errors:**
```bash
# Make sure all libraries are linked
# Check CMakeLists.txt has: freeglut opengl32 glu32 (Windows)
# or: ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} (Linux/Mac)
```

#### 7. Blank or Black Window

**Symptom:** Window opens but nothing renders

**Fixes:**
1. **Check OpenGL version**: Run `glxinfo | grep OpenGL` (Linux)
2. **Update graphics drivers**
3. **Try different equations**: Start with simple `x^2 + y^2`
4. **Check resolution**: Try lower value (30-40)

#### 8. Poor Performance / Lag

**Symptom:** Slow rendering, choppy rotation

**Fixes:**
- **Lower resolution**: Set to 30-40 instead of 50+
- **Simplify equation**: Complex expressions slow down evaluation
- **Reduce bounds**: Smaller range = fewer calculations
- **Update graphics drivers**

## 💡 Example Equations by Category

### Learning / Testing
```
x^2 + y^2              Simple paraboloid
x^2 - y^2              Saddle surface  
sin(x) + cos(y)        Basic waves
```

### Optimization Benchmarks
```
(1-x)^2 + 100*(y-x^2)^2              Rosenbrock (narrow valley)
(x^2+y-11)^2 + (x+y^2-7)^2           Himmelblau (4 minima)
x*sin(4*x) + 1.1*y*sin(2*y)          Schaffer function
```

### Beautiful Visualizations
```
exp(-(x^2 + y^2))                    Gaussian bell
sin(sqrt(x^2 + y^2))                 Ripples in pond
(1-x^2-y^2)*exp(-(x^2+y^2)/2)        Mexican hat
sin(5*x)*cos(5*y) + x^2 + y^2        Bumpy terrain
```

### Advanced
```
x*y*exp(-(x^2+y^2))                  Twisted surface
sqrt(abs(x*y))                       Corner singularity
log(1 + x^2 + y^2)                   Logarithmic growth
```

## 🏗️ Project Structure

```
project/
├── CMakeLists.txt           Build configuration
├── README.md                This file
├── DEBUGGING.md             Detailed debugging guide
│
├── include/                 Header files
│   ├── Point3D.h           3D point/vector class
│   ├── Surface.h           Surface base class
│   ├── Optimizer.h         Optimization algorithms
│   └── Visualizer.h        OpenGL visualization
│
├── src/                     Implementation files
│   ├── Point3D.cpp
│   ├── Surface.cpp
│   ├── Optimizer.cpp
│   └── Visualizer.cpp
│
├── EquationParser.h/.cpp    Mathematical expression parser
├── GUIManager.h/.cpp        GUI system (INPUT REQUIRED)
├── main_equation_gui.cpp    Main program with GUI
├── main.cpp                 Original demo version
│
├── build.sh                 Linux/Mac build script
└── run.bat                  Windows build & run script
```

## 🔬 Technical Details

### Equation Parser
- **Recursive descent** parser
- **Operator precedence**: `^` > `*`,`/` > `+`,`-`
- **Right-associative** power operator
- **Numerical derivatives** for optimization

### Gradient Descent
- **Update rule**: x_new = x_old - α * ∇f(x)
- **Convergence**: ||∇f|| < tolerance
- **Step tracking**: Saves path for visualization

### Visualization
- **Mesh generation**: Triangle strips
- **Lighting**: Per-vertex normals
- **Camera**: Orbital rotation around origin

## 🎓 Educational Applications

Perfect for:
- **Multivariable Calculus**: Visualizing functions f(x,y)
- **Optimization Theory**: Understanding gradient descent
- **Computer Graphics**: Learning 3D rendering
- **Numerical Methods**: Exploring numerical differentiation

## 📝 Configuration Tips

### Learning Rate Selection

| Surface Type | Recommended α |
|--------------|---------------|
| Simple bowl (x²+y²) | 0.01 - 0.1 |
| Waves | 0.01 - 0.05 |
| Rosenbrock | 0.0005 - 0.001 |

**Rule of thumb:** Start high (0.1), reduce if oscillating

### Resolution Selection

| Quality | Resolution | Performance |
|---------|------------|-------------|
| Preview | 20-30 | Fast |
| Normal | 50-70 | Balanced |
| High | 100-150 | Slow |

## 🤝 Contributing

Improvements welcome! Areas for enhancement:
- [ ] Analytical gradients for known functions
- [ ] Additional optimization algorithms (Adam, RMSprop)
- [ ] Constraint handling
- [ ] Equation presets library
- [ ] Export mesh to file formats
- [ ] Multiple optimization runs visualization

## 📜 License

Uses:
- **FreeGLUT**: MIT-style license
- **OpenGL**: Platform-specific

## 🙏 Acknowledgments

Built with:
- OpenGL for 3D graphics
- FreeGLUT for windowing
- Recursive descent parsing
- Numerical differentiation

---

**Happy 3D Math Exploring! 🎨📊🚀**

For issues, check the Debugging Guide above or examine console output.

---

**That's it! You're ready to explore 3D mathematics! 🎉**

For detailed documentation, see README.md
For troubleshooting, see DEBUGGING.md

# Debugging Guide - 3D Surface Optimizer

This guide helps you diagnose and fix common issues with the 3D Surface Optimizer project.

## Table of Contents
1. [Build Errors](#build-errors)
2. [Runtime Errors](#runtime-errors)
3. [Equation Parser Issues](#equation-parser-issues)
4. [Visualization Problems](#visualization-problems)
5. [Optimization Issues](#optimization-issues)
6. [Platform-Specific Issues](#platform-specific-issues)

---

## Build Errors

### Error: GUIManager.cpp Not Found

**Symptom:**
```
fatal error: GUIManager.cpp: No such file or directory
CMake Error: Cannot find source file: GUIManager.cpp
```

**Cause:** Missing implementation file

**Solution:**
1. Verify all files are present:
   ```bash
   ls -l *.cpp *.h src/*.cpp include/*.h
   ```

2. Required files checklist:
   - ✅ GUIManager.cpp (root directory)
   - ✅ GUIManager.h (root directory)
   - ✅ EquationParser.cpp and .h
   - ✅ main_equation_gui.cpp
   - ✅ src/Point3D.cpp, Surface.cpp, Optimizer.cpp, Visualizer.cpp
   - ✅ include/ versions of the headers

3. If missing, the file has been recreated in the improved version

---

### Error: GL/glut.h Not Found

**Symptom:**
```
fatal error: GL/glut.h: No such file or directory
```

**Cause:** FreeGLUT not installed or not in include path

**Solution:**

**Windows:**
```batch
1. Download FreeGLUT from http://freeglut.sourceforge.net/
2. Extract to C:\freeglut\
3. Verify structure:
   C:\freeglut\
   ├── include\GL\
   │   ├── glut.h
   │   └── freeglut.h
   ├── lib\
   │   └── freeglut.lib
   └── bin\
       └── freeglut.dll

4. Or edit CMakeLists.txt:
   set(FREEGLUT_DIR "D:/your/path/to/freeglut")
```

**Linux:**
```bash
sudo apt-get update
sudo apt-get install freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

**macOS:**
```bash
brew install freeglut
# If brew not installed:
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

---

### Error: Linking Failed - Undefined Reference to glut*

**Symptom:**
```
undefined reference to `glutInit'
undefined reference to `glutCreateWindow'
```

**Cause:** FreeGLUT library not linked properly

**Solution:**

1. Check CMakeLists.txt has correct linking:
   ```cmake
   # Windows
   target_link_libraries(optimizer freeglut opengl32 glu32)
   
   # Linux/Mac
   target_link_libraries(optimizer ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
   ```

2. Verify library location:
   **Windows:**
   ```batch
   dir C:\freeglut\lib\freeglut.lib
   ```
   
   **Linux:**
   ```bash
   ldconfig -p | grep glut
   ```

3. Clean and rebuild:
   ```bash
   rm -rf build
   mkdir build && cd build
   cmake .. && make
   ```

---

### Error: C++17 Required

**Symptom:**
```
error: 'std::function' has not been declared
CMake Error: C++ standard 17 is required
```

**Cause:** Compiler doesn't support C++17 or isn't configured

**Solution:**

1. Check compiler version:
   ```bash
   g++ --version  # Should be 7.0 or higher
   ```

2. Update compiler:
   **Ubuntu/Debian:**
   ```bash
   sudo apt-get install g++-9
   export CXX=g++-9
   ```
   
   **Windows MinGW:**
   - Download latest MinGW-w64 from https://winlibs.com/
   - Add to PATH

3. Force CMake to use newer compiler:
   ```bash
   cmake .. -DCMAKE_CXX_COMPILER=g++-9
   ```

---

## Runtime Errors

### Error: freeglut.dll Not Found (Windows)

**Symptom:**
```
The code execution cannot proceed because freeglut.dll was not found.
```

**Solution:**

1. **Copy DLL manually:**
   ```batch
   copy C:\freeglut\bin\x64\freeglut.dll build\
   ```

2. **Add to system PATH:**
   ```batch
   setx PATH "%PATH%;C:\freeglut\bin\x64"
   ```

3. **Verify DLL location:**
   ```batch
   dir build\freeglut.dll
   ```

---

### Error: Segmentation Fault / Access Violation

**Symptom:**
Program crashes immediately with seg fault

**Common Causes & Solutions:**

1. **Null Pointer in Parser:**
   - Check equation is set before evaluation
   - Verify variables are initialized

2. **OpenGL Context Not Created:**
   - Ensure glutInit() called before any GL calls
   - Check window creation succeeded

3. **Invalid Memory Access:**
   - Debug with gdb (Linux) or Visual Studio debugger (Windows)
   ```bash
   gdb ./optimizer
   (gdb) run
   (gdb) backtrace  # After crash
   ```

---

## Equation Parser Issues

### Issue: "Invalid Equation" Error

**Common Mistakes:**

1. **Missing Multiplication:**
   - ❌ `2x` → ✅ `2*x`
   - ❌ `(x+1)(y+1)` → ✅ `(x+1)*(y+1)`
   - ❌ `xy` → ✅ `x*y`

2. **Function Syntax:**
   - ❌ `sin x` → ✅ `sin(x)`
   - ❌ `sqrt x+y` → ✅ `sqrt(x+y)`

3. **Unbalanced Parentheses:**
   - ❌ `(x+y` → ✅ `(x+y)`
   - ❌ `sin(x))` → ✅ `sin(x)`

4. **Invalid Characters:**
   - ❌ `x²` → ✅ `x^2`
   - ❌ `x×y` → ✅ `x*y`

5. **Wrong Power Notation:**
   - ❌ `x**2` (Python style) → ✅ `x^2` or `pow(x,2)`

---

### Issue: "Undefined Variable" Error

**Symptom:**
```
Undefined variable: z
```

**Cause:** Equation uses variables other than x, y

**Solution:**
- Only use `x` and `y` in equations
- If you need `z`, express it in terms of `x` and `y`
- Example: Instead of `z = f(x,y,z)`, use `f(x,y,0)`

---

### Issue: Equation Evaluates to NaN or Infinity

**Common Causes:**

1. **Division by Zero:**
   ```
   Bad: 1/x  (when x=0)
   Fix: 1/(x+0.001)  or  x==0 ? large_value : 1/x
   ```

2. **Log of Negative/Zero:**
   ```
   Bad: log(x)  (when x≤0)
   Fix: log(abs(x)+1)
   ```

3. **Square Root of Negative:**
   ```
   Bad: sqrt(x-10)  (when x<10)
   Fix: sqrt(abs(x-10))
   ```

**Debug Steps:**
1. Test equation at specific points:
   ```cpp
   std::cout << parser.evaluate(0, 0) << std::endl;
   std::cout << parser.evaluate(1, 1) << std::endl;
   ```

2. Check for invalid values:
   ```cpp
   double z = parser.evaluate(x, y);
   if (std::isnan(z) || std::isinf(z)) {
       std::cout << "Invalid at (" << x << "," << y << ")" << std::endl;
   }
   ```

---

## Visualization Problems

### Issue: Blank/Black Window

**Symptoms:**
- Window opens but shows nothing
- All black screen
- Window freezes

**Solutions:**

1. **Check OpenGL version:**
   ```bash
   glxinfo | grep "OpenGL version"  # Linux
   ```
   - Requires OpenGL 2.1 or higher

2. **Update Graphics Drivers:**
   - NVIDIA: Download from nvidia.com
   - AMD: Download from amd.com
   - Intel: Use Windows Update or intel.com

3. **Test with simple equation:**
   - Try `x^2 + y^2` first
   - If this works, issue is with complex equation

4. **Check bounds:**
   - Equation might be outside visible range
   - Try bounds [-10, 10] × [-10, 10]

5. **Verify lighting:**
   - In Visualizer.cpp, check GL_LIGHTING is enabled
   - Verify light position is set

---

### Issue: Surface Looks Wrong/Distorted

**Possible Causes:**

1. **Incorrect Bounds:**
   - Surface extends beyond viewing area
   - Solution: Adjust xMin, xMax, yMin, yMax

2. **Resolution Too Low:**
   - Surface appears blocky
   - Solution: Increase resolution (try 70-100)

3. **Equation Has Discontinuities:**
   - E.g., `1/x` near x=0
   - Solution: Add small offset or use smooth function

4. **Normal Calculation Issues:**
   - Surface shading looks off
   - Check numerical gradient calculation in Surface.cpp

---

### Issue: Poor Performance / Laggy Rendering

**Symptoms:**
- Slow rotation
- Low frame rate
- Stuttering

**Solutions:**

1. **Reduce Resolution:**
   - Try 30-40 instead of 50+
   - Impact on quality is minimal

2. **Simplify Equation:**
   - Complex expressions (many trig functions) slow evaluation
   - Pre-calculate constants

3. **Reduce Viewing Bounds:**
   - Smaller range = fewer mesh points
   - Try [-5, 5] × [-5, 5]

4. **Disable Optimization:**
   - Run without optimization to reduce overhead
   - Set "Run Optimization" to 'n'

5. **Check System Resources:**
   ```bash
   top  # Linux
   # Look for high CPU usage
   ```

---

## Optimization Issues

### Issue: Optimization Doesn't Converge

**Symptoms:**
- Iterations reach maximum
- "Converged: No" in output
- Point oscillates or diverges

**Solutions:**

1. **Reduce Learning Rate:**
   ```
   Current: 0.1
   Try: 0.01, 0.001, 0.0001
   ```
   - Smaller steps = more stable
   - May need more iterations

2. **Change Starting Point:**
   - Try different (startX, startY)
   - Some surfaces have multiple local minima

3. **Check Surface Type:**
   - Saddle surfaces have no minimum
   - Planes have no minimum
   - Unbounded surfaces diverge

4. **Verify Gradient Calculation:**
   - Add debug output in Optimizer.cpp:
   ```cpp
   std::cout << "Gradient: " << grad.getX() << ", " << grad.getY() << std::endl;
   ```

---

### Issue: Found Minimum is Wrong

**Symptoms:**
- Minimum doesn't match expected value
- Visual path doesn't reach lowest point

**Causes & Solutions:**

1. **Local vs Global Minimum:**
   - Algorithm found local minimum
   - Try different starting points
   - Some functions have many minima

2. **Learning Rate Too High:**
   - Overshooting minimum
   - Reduce learning rate by 10×

3. **Tolerance Too Large:**
   - Stopping too early
   - In Optimizer.cpp, reduce tolerance:
   ```cpp
   GradientDescent gd(&surface, 0.01, 1000, 1e-8);  // was 1e-6
   ```

4. **Numerical Precision:**
   - Gradients calculated numerically
   - Inherent small errors
   - Expected for non-analytical gradients

---

## Platform-Specific Issues

### Windows Specific

**Issue: MinGW vs MSVC Conflicts**

If you have both installed:
```batch
# Clean all CMake cache
rmdir /s /q build
mkdir build && cd build

# Force generator
cmake .. -G "MinGW Makefiles"
# OR
cmake .. -G "Visual Studio 16 2019"
```

**Issue: PATH Not Updated**

After installing tools, restart Command Prompt or:
```batch
refreshenv  # If using Chocolatey
# OR logout and login
```

---

### Linux Specific

**Issue: Missing X11 Development Files**

```bash
sudo apt-get install libx11-dev libxi-dev libxmu-dev
```

**Issue: OpenGL Not Found**

```bash
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
```

---

### macOS Specific

**Issue: OpenGL Deprecated**

macOS 10.14+ deprecated OpenGL. It still works but may show warnings.

**Solution:** Compile with:
```bash
cmake .. -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations"
```

**Issue: FreeGLUT from Homebrew Not Found**

```bash
# After brew install freeglut
brew --prefix freeglut  # Note the path

# Then in CMakeLists.txt:
set(GLUT_ROOT_PATH "/usr/local/opt/freeglut")
```

---

## General Debugging Tips

### Enable Verbose Build Output

```bash
cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
make VERBOSE=1
```

### Add Debug Symbols

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Then use debugger:
```bash
gdb ./optimizer
(gdb) break main
(gdb) run
(gdb) next  # Step through
```

### Check All File Permissions

```bash
chmod +x build.sh
chmod 644 *.cpp *.h
```

### Validate CMakeLists.txt Syntax

```bash
cmake -P CMakeLists.txt  # Dry run
```

---

## Getting Help

### Useful Debug Information to Collect

When asking for help, provide:

1. **System Information:**
   ```bash
   uname -a  # Linux/Mac
   # OR
   systeminfo  # Windows
   ```

2. **Compiler Version:**
   ```bash
   g++ --version
   cmake --version
   ```

3. **Full Error Message:**
   - Copy entire error output
   - Include stack trace if available

4. **Build Command Used:**
   - Exact cmake command
   - Exact make/build command

5. **Equation Attempted:**
   - What you typed in GUI
   - Expected vs actual behavior

---

## Quick Fixes Checklist

Before diving deep, try these:

- [ ] Clean build directory: `rm -rf build && mkdir build`
- [ ] Update system: `sudo apt-get update && upgrade` (Linux)
- [ ] Restart computer (especially after installing new tools)
- [ ] Try simple equation first: `x^2 + y^2`
- [ ] Check all files present: `ls -l *.cpp *.h src/*.cpp include/*.h`
- [ ] Verify FreeGLUT installed: `ldconfig -p | grep glut` (Linux)
- [ ] Test with default parameters
- [ ] Check console output for specific errors
- [ ] Try different starting points for optimization
- [ ] Reduce resolution to 30 and test

---

## Still Having Issues?

1. Check the main README.md for basic setup
2. Review example equations that are known to work
3. Compare your files with the original distribution
4. Try the demo version: `./optimizer_demo`
5. Check if issue is equation-specific or general

---

**Last Updated:** January 2026
**Version:** 1.0


# 3D Surface Optimizer - Complete Technical Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Mathematical Foundations](#mathematical-foundations)
3. [Architecture & Design](#architecture--design)
4. [Core Components Deep Dive](#core-components-deep-dive)
5. [Optimization Algorithms](#optimization-algorithms)
6. [Equation Parser Implementation](#equation-parser-implementation)
7. [3D Visualization System](#3d-visualization-system)
8. [Build System & Dependencies](#build-system--dependencies)
9. [Usage Guide](#usage-guide)
10. [Advanced Topics](#advanced-topics)

---

## Project Overview

### What This Project Does

This is a **3D Surface Visualization and Optimization System** that allows users to:

1. **Define mathematical surfaces** using equations with variables x, y, z
2. **Visualize surfaces in 3D** with interactive rotation and zoom
3. **Find local minima** using optimization algorithms (Gradient Descent or Newton's Method)
4. **Visualize the optimization path** in real-time on the 3D surface

### Key Features

- **Interactive Equation Input**: Enter any mathematical expression
- **Real-time 3D Rendering**: OpenGL-based visualization with lighting and shading
- **Multiple Optimization Methods**: Gradient Descent and Newton's Method
- **Path Visualization**: See how the optimizer navigates the surface
- **Configurable Parameters**: Adjust learning rate, start position, mesh resolution

### Technology Stack

- **Language**: C++17
- **Graphics**: OpenGL with FreeGLUT
- **Build System**: CMake
- **Mathematical Operations**: Standard C++ math library
- **Parser**: Custom recursive descent parser

---

## Mathematical Foundations

### 1. Surface Representation

A 3D surface is mathematically represented as a function:

```
z = f(x, y)
```

Where:
- `(x, y)` are coordinates in the horizontal plane
- `z` is the height/value at that point
- `f` is any continuous function

**Examples:**
- Paraboloid: `z = x² + y²` (bowl-shaped)
- Saddle: `z = x² - y²` (horse saddle shape)
- Custom: `z = sin(x) * cos(y) + x²`

### 2. Gradients and Partial Derivatives

#### What is a Gradient?

The **gradient** (∇f) is a vector that points in the direction of steepest ascent on the surface:

```
∇f(x, y) = (∂f/∂x, ∂f/∂y)
```

**Components:**
- `∂f/∂x`: Partial derivative with respect to x (how z changes as x changes, y fixed)
- `∂f/∂y`: Partial derivative with respect to y (how z changes as y changes, x fixed)

#### Numerical Approximation

Since we work with arbitrary functions, we use **finite differences** to approximate derivatives:

```cpp
∂f/∂x ≈ [f(x + h, y) - f(x - h, y)] / (2h)
```

Where `h = 0.0001` is a small step size. This is called the **central difference** method.

**Why Central Difference?**
- More accurate than forward difference: `[f(x+h) - f(x)] / h`
- Reduces truncation error to O(h²) instead of O(h)

### 3. Optimization Theory

#### Local Minima

A point `(x*, y*)` is a **local minimum** if:
```
f(x*, y*) ≤ f(x, y)
```
for all points in a neighborhood around `(x*, y*)`.

#### Necessary Condition

At a minimum, the gradient must be zero (or very small):
```
∇f(x*, y*) = (0, 0)
```

This means the surface is "flat" at that point - no slope in any direction.

#### Hessian Matrix

The **Hessian** is a matrix of second derivatives that describes the curvature:

```
H = [ ∂²f/∂x²    ∂²f/∂x∂y ]
    [ ∂²f/∂x∂y   ∂²f/∂y²  ]
```

**Properties:**
- If H is positive definite at a critical point → local minimum
- If H is negative definite → local maximum
- If H has mixed signs → saddle point

---

## Architecture & Design

### Object-Oriented Design

The project follows **SOLID principles** with clear separation of concerns:

```
┌─────────────────────────────────────────────────────┐
│                  GUIManager                         │
│  (Orchestrates the entire application)              │
└──────────────┬──────────────────────────────────────┘
               │
       ┌───────┴───────┐
       │               │
┌──────▼──────┐  ┌────▼─────────┐
│EquationParser│  │ Visualizer  │
│(Parses math) │  │(3D Graphics)│
└──────┬───────┘  └────┬─────────┘
       │               │
       │         ┌─────▼──────┐
       │         │  Surface   │
       │         │(Base Class)│
       │         └─────┬──────┘
       │               │
       │         ┌─────┴──────────────┐
       │         │                    │
       │    ┌────▼────────┐    ┌─────▼──────┐
       │    │ Paraboloid  │    │CustomSurface│
       │    │             │    │(User Eqn)   │
       │    └─────────────┘    └──────┬──────┘
       │                              │
       └──────────────────────────────┘
                   │
            ┌──────▼──────┐
            │  Optimizer  │
            │ (Abstract)  │
            └──────┬──────┘
                   │
         ┌─────────┴──────────┐
         │                    │
    ┌────▼─────────┐   ┌─────▼────────┐
    │GradientDescent│   │NewtonOptimizer│
    └───────────────┘   └──────────────┘
```

### Design Patterns Used

#### 1. Strategy Pattern (Optimizer)

```cpp
class Optimizer {
    virtual OptimizationResult optimize(double x, double y) = 0;
};

class GradientDescent : public Optimizer { ... };
class NewtonOptimizer : public Optimizer { ... };
```

**Why?** Allows swapping optimization algorithms without changing client code.

#### 2. Template Method Pattern (Surface)

```cpp
class Surface {
    virtual double evaluate(double x, double y) const = 0;
    // Common implementations use evaluate()
    Point3D gradient(double x, double y) const { ... }
};
```

**Why?** Base class provides common functionality, derived classes specialize behavior.

#### 3. Singleton Pattern (Visualizer)

```cpp
static Visualizer* instance;
static void displayCallback() {
    if (instance) instance->display();
}
```

**Why?** GLUT requires static callback functions, singleton provides access to instance.

#### 4. Facade Pattern (GUIManager)

```cpp
class GUIManager {
    // Hides complexity of Parser, Visualizer, Optimizer
    void initialize();
    void run();
};
```

**Why?** Simplifies the interface for the complex subsystem.

---

## Core Components Deep Dive

### 1. Point3D Class (`Point3D.h`, `Point3D.cpp`)

**Purpose**: Represents a 3D point or vector.

#### Key Concepts

```cpp
class Point3D {
private:
    double x, y, z;
public:
    Point3D operator+(const Point3D& other) const;  // Vector addition
    Point3D operator*(double scalar) const;          // Scalar multiplication
    double magnitude() const;                        // ||v|| = √(x²+y²+z²)
    Point3D normalize() const;                       // v/||v||
};
```

#### Mathematical Operations

**Vector Addition**: Combines two position vectors
```
v1 + v2 = (x1 + x2, y1 + y2, z1 + z2)
```

**Magnitude**: Distance from origin
```
||v|| = √(x² + y² + z²)
```

**Normalization**: Creates unit vector (length = 1)
```
v̂ = v / ||v||
```

### 2. Surface Class Hierarchy (`Surface.h`, `Surface.cpp`)

#### Abstract Base Class

```cpp
class Surface {
public:
    virtual double evaluate(double x, double y) const = 0;  // Pure virtual
    virtual double partialX(double x, double y) const;      // Numerical derivative
    virtual double partialY(double x, double y) const;
    Point3D gradient(double x, double y) const;
};
```

**Design Decision**: Why virtual functions?
- Allows polymorphism: `Surface* s = new Paraboloid();`
- Different surfaces can have different implementations
- Enables analytical derivatives for known functions

#### Paraboloid Implementation

```cpp
class Paraboloid : public Surface {
public:
    double evaluate(double x, double y) const override {
        return x * x + y * y;  // z = x² + y²
    }
    
    double partialX(double x, double y) const override {
        return 2 * x;  // Analytical: d/dx(x² + y²) = 2x
    }
};
```

**Optimization**: Uses analytical derivatives instead of numerical approximation for better performance and accuracy.

#### CustomSurface Implementation

```cpp
class CustomSurface : public Surface {
private:
    std::function<double(double, double)> func;
public:
    CustomSurface(std::function<double(double, double)> f) : func(f) {}
    
    double evaluate(double x, double y) const override {
        return func(x, y);  // Calls user-provided function
    }
};
```

**C++ Feature**: Uses `std::function` - a type-erased wrapper for any callable:
- Lambda functions: `[](double x, double y) { return x*x; }`
- Function pointers
- Functors (objects with `operator()`)

#### Mesh Generation

```cpp
std::vector<Point3D> generateMesh(double xMin, double xMax, 
                                  double yMin, double yMax, 
                                  int resolution) const {
    // Creates (resolution+1)² points
    for (int i = 0; i <= resolution; ++i) {
        for (int j = 0; j <= resolution; ++j) {
            double x = xMin + i * xStep;
            double y = yMin + j * yStep;
            double z = evaluate(x, y);
            mesh.push_back(Point3D(x, y, z));
        }
    }
}
```

**Algorithm**: Regular grid sampling
- Divides domain into equal steps
- Evaluates function at each grid point
- Used for rendering the surface

---

## Optimization Algorithms

### 1. Gradient Descent (`GradientDescent` class)

#### The Algorithm

**Intuition**: Walk downhill in the direction of steepest descent.

**Update Rule**:
```
x(t+1) = x(t) - α * ∂f/∂x
y(t+1) = y(t) - α * ∂f/∂y
```

Where:
- `α` is the learning rate (step size)
- `∂f/∂x, ∂f/∂y` are components of the gradient

#### Implementation

```cpp
OptimizationResult GradientDescent::optimize(double startX, double startY) {
    double x = startX, y = startY;
    
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Store current position for visualization
        result.path.push_back(Point3D(x, y, surface->evaluate(x, y)));
        
        // Calculate gradient
        Point3D grad = surface->gradient(x, y);
        
        // Check convergence: ||∇f|| < tolerance
        double gradMag = sqrt(grad.getX()² + grad.getY()²);
        if (gradMag < tolerance) {
            result.converged = true;
            break;
        }
        
        // Update position
        x = x - learningRate * grad.getX();
        y = y - learningRate * grad.getY();
    }
    
    return result;
}
```

#### Hyperparameters

**Learning Rate (α)**:
- Too small → slow convergence
- Too large → overshooting, oscillation, divergence
- Typical: 0.01 - 0.1

**Tolerance**:
- Stopping criterion: ||∇f|| < tolerance
- Prevents infinite iterations near minimum
- Typical: 1e-6

#### Convergence Analysis

**When does it converge?**
- Function is convex (bowl-shaped)
- Learning rate is appropriately chosen: `0 < α < 2/L` where L is Lipschitz constant

**Convergence Rate**: O(1/k) for convex functions (k iterations)

### 2. Newton's Method (`NewtonOptimizer` class)

#### The Algorithm

**Intuition**: Uses curvature information (second derivatives) for faster convergence.

**Update Rule**:
```
[x(t+1)]   [x(t)]         [∂f/∂x]
[y(t+1)] = [y(t)] - α H⁻¹ [∂f/∂y]
```

Where H is the Hessian matrix.

#### Hessian Matrix Computation

```cpp
double NewtonOptimizer::partialXX(double x, double y) const {
    const double h = 0.0001;
    // Second derivative: d²f/dx² ≈ [f'(x+h) - f'(x-h)] / (2h)
    return (surface->partialX(x + h, y) - 
            surface->partialX(x - h, y)) / (2 * h);
}

double NewtonOptimizer::partialXY(double x, double y) const {
    // Mixed partial: ∂²f/∂x∂y ≈ [fx(x,y+h) - fx(x,y-h)] / (2h)
    return (surface->partialX(x, y + h) - 
            surface->partialX(x, y - h)) / (2 * h);
}
```

**Numerical Stability**: Using central differences for second derivatives introduces more error but is still stable for well-behaved functions.

#### Hessian Inversion

For a 2×2 matrix:
```
H = [a  b]    H⁻¹ = 1/(ad-b²) [ d  -b]
    [b  d]                    [-b   a]
```

```cpp
double det = fxx * fyy - fxy * fxy;
if (abs(det) < 1e-10) {
    // Singular matrix - can't invert
    // Happens at saddle points or flat regions
}

double invH11 = fyy / det;
double invH12 = -fxy / det;
double invH22 = fxx / det;
```

#### Update Step

```cpp
// Newton direction: d = -H⁻¹∇f
double dx = invH11 * gx + invH12 * gy;
double dy = invH12 * gx + invH22 * gy;

// Update with learning rate (damped Newton's method)
x = x - learningRate * dx;
y = y - learningRate * dy;
```

**Damping**: Using `learningRate < 1` makes it more stable but slower.

#### Comparison: Gradient Descent vs Newton's Method

| Aspect | Gradient Descent | Newton's Method |
|--------|------------------|-----------------|
| **Convergence Rate** | Linear O(1/k) | Quadratic O(1/k²) |
| **Computation per Iteration** | O(n) - just gradient | O(n²) - Hessian + inversion |
| **Memory** | Low | Higher (store Hessian) |
| **Best For** | Large problems, rough terrain | Small problems, smooth surfaces |
| **Robustness** | More robust | Can fail at saddle points |

---

## Equation Parser Implementation

### Why We Need a Parser

Users enter equations as strings: `"x^2 + sin(y) * 3"`. We need to:
1. **Tokenize**: Break into meaningful pieces
2. **Parse**: Build a syntax tree
3. **Evaluate**: Compute numerical result

### Tokenization Process

```cpp
enum TokenType { NUMBER, VARIABLE, OPERATOR, FUNCTION, LPAREN, RPAREN };

void tokenize() {
    // "x^2 + sin(y)" becomes:
    // [VARIABLE:x] [OPERATOR:^] [NUMBER:2] [OPERATOR:+] 
    // [FUNCTION:sin] [LPAREN] [VARIABLE:y] [RPAREN]
}
```

**State Machine**: Reads character by character, identifying patterns:
- Digits → NUMBER
- Letters → VARIABLE or FUNCTION
- `+, -, *, /, ^` → OPERATOR
- `(, )` → LPAREN, RPAREN

### Recursive Descent Parsing

**Grammar** (in BNF notation):
```
expression → term (('+' | '-') term)*
term       → power (('*' | '/') power)*
power      → unary ('^' power)?
unary      → ('+' | '-')? primary
primary    → NUMBER | VARIABLE | FUNCTION '(' expression ')' | '(' expression ')'
```

**Operator Precedence** (highest to lowest):
1. Parentheses `()`
2. Functions `sin()`, `cos()`
3. Unary `+`, `-`
4. Exponentiation `^` (right associative)
5. Multiplication, Division `*`, `/`
6. Addition, Subtraction `+`, `-`

### Parsing Implementation

```cpp
double parseExpression() {
    // expression → term (('+' | '-') term)*
    double result = parseTerm();
    
    while (current token is '+' or '-') {
        string op = current token;
        advance();
        double right = parseTerm();
        
        if (op == "+") result += right;
        else result -= right;
    }
    
    return result;
}

double parseTerm() {
    // term → power (('*' | '/') power)*
    double result = parsePower();
    
    while (current token is '*' or '/') {
        string op = current token;
        advance();
        double right = parsePower();
        
        if (op == "*") result *= right;
        else result /= right;
    }
    
    return result;
}

double parsePower() {
    // power → unary ('^' power)?    [RIGHT ASSOCIATIVE]
    double result = parseUnary();
    
    if (current token is '^') {
        advance();
        double exponent = parsePower();  // Recursive for right-associativity
        result = pow(result, exponent);
    }
    
    return result;
}
```

**Right Associativity**: `2^3^2` = `2^(3^2)` = `2^9` = 512, not `(2^3)^2` = 64

### Function Calls

```cpp
double parsePrimary() {
    if (token is FUNCTION) {
        string funcName = token.value;
        advance();
        expect('(');
        
        if (funcName is binary function like "pow") {
            double arg1 = parseExpression();
            expect(',');
            double arg2 = parseExpression();
            expect(')');
            return binaryFunctions[funcName](arg1, arg2);
        } else {
            double arg = parseExpression();
            expect(')');
            return functions[funcName](arg);
        }
    }
}
```

### Supported Functions

**Unary Functions** (one argument):
- `sin(x)`, `cos(x)`, `tan(x)` - Trigonometric
- `exp(x)` - e^x
- `log(x)`, `ln(x)` - Natural logarithm
- `log10(x)` - Base-10 logarithm
- `sqrt(x)` - Square root
- `abs(x)` - Absolute value
- `floor(x)`, `ceil(x)` - Rounding

**Binary Functions** (two arguments):
- `pow(x, y)` - x^y
- `min(x, y)` - Minimum
- `max(x, y)` - Maximum

### Implicit Multiplication Handling

```cpp
string normalizeEquation(const string& eq) {
    // Convert: "2x" → "2*x"
    // Convert: "2(x+y)" → "2*(x+y)"
    // Convert: "(x)(y)" → "(x)*(y)"
    
    if (isdigit(current) && isalpha(next))
        insert '*' between them;
    if (isdigit(current) && next == '(')
        insert '*' between them;
    if (current == ')' && next == '(')
        insert '*' between them;
}
```

**Edge Case**: `sin(x)` should NOT become `sin*(x)` - check if it's a known function.

### Error Handling

```cpp
bool validate(string& errorMessage) {
    try {
        tokenize();
        checkBalancedParentheses();
        evaluateWithDummyVariables();
        return true;
    } catch (exception& e) {
        errorMessage = e.what();
        return false;
    }
}
```

**Common Errors**:
- Unbalanced parentheses
- Division by zero
- Unknown variables
- Malformed expressions

---

## 3D Visualization System

### OpenGL Pipeline Overview

```
Vertices → Vertex Processing → Primitive Assembly → Rasterization → Fragment Processing → Display
```

### FreeGLUT Setup

```cpp
void Visualizer::initialize(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Surface Optimizer");
    
    glEnable(GL_DEPTH_TEST);      // Z-buffer for hidden surface removal
    glEnable(GL_LIGHTING);         // Phong lighting model
    glEnable(GL_LIGHT0);           // Primary light source
    glEnable(GL_COLOR_MATERIAL);   // Allow material colors
}
```

**Double Buffering**: Prevents flickering by drawing to back buffer, then swapping.

**Depth Test**: Ensures closer objects appear in front of farther ones.

### Camera Positioning

```cpp
void display() {
    glLoadIdentity();
    
    // Camera at (0, 0, zoom) looking at (0, 0, 0), up is (0, 1, 0)
    gluLookAt(0, 0, zoom,    // Eye position
              0, 0, 0,        // Look-at point
              0, 1, 0);       // Up vector
    
    // Apply rotations
    glRotatef(rotationX, 1, 0, 0);  // Rotate around X-axis
    glRotatef(rotationY, 0, 1, 0);  // Rotate around Y-axis
}
```

**View Matrix**: Transforms world coordinates to camera coordinates.

### Surface Rendering

#### Triangle Strip Method

```cpp
void drawSurface() {
    for (int i = 0; i < resolution; ++i) {
        glBegin(GL_TRIANGLE_STRIP);
        
        for (int j = 0; j <= resolution; ++j) {
            double x1 = xMin + i * xStep;
            double x2 = xMin + (i + 1) * xStep;
            double y = yMin + j * yStep;
            
            double z1 = surface->evaluate(x1, y);
            double z2 = surface->evaluate(x2, y);
            
            // Calculate normals for lighting
            Point3D grad1 = surface->gradient(x1, y);
            Point3D normal1(-grad1.getX(), -grad1.getY(), 1.0);
            normal1 = normal1.normalize();
            
            glNormal3f(normal1.getX(), normal1.getY(), normal1.getZ());
            glVertex3f(x1, y, z1);
            
            glNormal3f(normal2.getX(), normal2.getY(), normal2.getZ());
            glVertex3f(x2, y, z2);
        }
        
        glEnd();
    }
}
```

**Why Triangle Strips?**
- Efficient: Shares vertices between adjacent triangles
- For N vertices: (N-2) triangles instead of N/3

**Normal Calculation**:
```
If surface is z = f(x, y), the normal is proportional to:
n = (-∂f/∂x, -∂f/∂y, 1)
```

This is because the surface can be written as: `F(x,y,z) = z - f(x,y) = 0`
And the gradient of F is the normal: `∇F = (-fx, -fy, 1)`

### Lighting Model

```cpp
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  // Directional light
GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};   // Ambient component
GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1.0};   // Diffuse component

glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
```

**Phong Reflection Model**:
```
I = Ia*ka + Id*kd*(N·L) + Is*ks*(R·V)^n
```

Where:
- `Ia, Id, Is` = ambient, diffuse, specular light intensities
- `ka, kd, ks` = material reflection coefficients
- `N` = surface normal
- `L` = light direction
- `R` = reflection direction
- `V` = view direction
- `n` = shininess exponent

### Path Visualization

```cpp
void drawOptimizationPath() {
    // Draw path as red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    
    glBegin(GL_LINE_STRIP);
    for (const auto& point : optResult->path) {
        glVertex3f(point.getX(), point.getY(), point.getZ());
    }
    glEnd();
    
    // Start point: green sphere
    Point3D start = optResult->path.front();
    glPushMatrix();
    glTranslatef(start.getX(), start.getY(), start.getZ());
    glutSolidSphere(0.2, 20, 20);  // radius, slices, stacks
    glPopMatrix();
    
    // End point: red sphere
    Point3D end = optResult->path.back();
    glPushMatrix();
    glTranslatef(end.getX(), end.getY(), end.getZ());
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}
```

**Matrix Stack**: `glPushMatrix()` saves current transformation, `glPopMatrix()` restores it.

### Interactive Controls

```cpp
void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': instance->rotationX += 5.0f; break;  // Rotate up
        case 's': instance->rotationX -= 5.0f; break;  // Rotate down
        case 'a': instance->rotationY -= 5.0f; break;  // Rotate left
        case 'd': instance->rotationY += 5.0f; break;  // Rotate right
        case '+': instance->zoom -= 2.0f; break;        // Zoom in
        case '-': instance->zoom += 2.0f; break;        // Zoom out
        case 'r':                                       // Reset view
            instance->rotationX = 30.0f;
            instance->rotationY = 45.0f;
            instance->zoom = 30.0f;
            break;
        case 27: exit(0); break;  // ESC
    }
    glutPostRedisplay();  // Request redraw
}
```

---

## Build System & Dependencies

### CMake Configuration

```cmake
cmake_minimum_required(VERSION 3.10)
project(SurfaceOptimizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

**Why C++17?**
- `std::function` for callable wrappers
- Structured bindings (if used)
- Better type inference

### Platform-Specific Configuration

#### Windows

```cmake
if(WIN32)
    set(FREEGLUT_DIR "C:/freeglut" CACHE PATH "FreeGLUT installation")
    include_directories(${FREEGLUT_DIR}/include)
    link_directories(${FREEGLUT_DIR}/lib/x64)
    
    target_link_libraries(optimizer freeglut opengl32 glu32)
    
    # Copy DLL to build directory
    add_custom_command(TARGET optimizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_DIR}/bin/x64/freeglut.dll"
        $<TARGET_FILE_DIR:optimizer>
    )
endif()
```

#### Linux/Mac

```cmake
else()
    find_package(GLUT REQUIRED)
    find_package(OpenGL REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
    
    target_link_libraries(optimizer 
        ${GLUT_LIBRARIES} 
        ${OPENGL_LIBRARIES} 
        m)  # Math library
endif()
```

### Executables

**Two targets**:
1. `optimizer`: Main program with equation GUI
2. `optimizer_demo`: Original hardcoded demo

```cmake
add_executable(optimizer 
    ${COMMON_SOURCES}
    ${EQUATION_SOURCES}
    main_equation_gui.cpp
)

add_executable(optimizer_demo 
    ${COMMON_SOURCES}
    main.cpp
)
```

### Dependencies

**Required**:
- CMake 3.10+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- FreeGLUT (OpenGL Utility Toolkit)
- OpenGL libraries

**Installation**:

Ubuntu/Debian:
```bash
sudo apt-get install cmake build-essential freeglut3-dev
```

Windows:
1. Install CMake from cmake.org
2. Install MinGW-w64 or Visual Studio
3. Download FreeGLUT from freeglut.sourceforge.net
4. Extract to C:\freeglut

---

## Usage Guide

### Building the Project

#### Linux/Mac

```bash
chmod +x build.sh
./build.sh
```

#### Windows

```bat
run.bat
```

Or manually:
```bat
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make
```

### Running the Program

```bash
cd build
./optimizer          # Linux
optimizer.exe        # Windows
```

### Using the Equation GUI

#### Step 1: Enter Equation

Example inputs:
- `x^2 + y^2` - Paraboloid
- `sin(x) * cos(y)` - Wave pattern
- `x^2 - y^2` - Saddle surface
- `exp(-(x^2 + y^2))` - Gaussian
- `pow(x, 2) + 2*x*y + pow(y, 2)` - Using pow function

**Tips**:
- Use `^` or `**` for exponentiation
- Implicit multiplication: `2x` becomes `2*x`
- Case sensitive: `X` and `x` are different

#### Step 2: Configuration

**Optimize** [y/n]: Run optimization?
- `y`: Find minimum and show path
- `n`: Just visualize surface

**Start X, Start Y**: Initial point for optimization
- Choose a point in your domain
- Different starts may find different local minima

**Learning Rate** (α): Step size for optimization
- Small (0.001-0.01): Slow but stable
- Medium (0.01-0.1): Balanced
- Large (>0.1): Fast but may diverge

**Domain** (xMin, xMax, yMin, yMax): Viewing region
- Should contain interesting features
- Affects mesh resolution

**Resolution**: Number of grid points
- Higher = smoother surface but slower rendering
- 50-100 is typical

#### Step 3: 3D Visualization

**Mouse/Keyboard Controls**:
- `W/S`: Pitch rotation (up/down)
- `A/D`: Yaw rotation (left/right)
- `+/-`: Zoom in/out
- `R`: Reset camera
- `ESC`: Exit

### Example Sessions

#### Example 1: Finding Minimum of Paraboloid

```
Equation: x^2 + y^2
Optimize: y
Start X: 5
Start Y: 5
Learning Rate: 0.05
X Range: -10 to 10
Y Range: -10 to 10
Resolution: 50
```

**Expected Result**: Converges to (0, 0, 0) from (5, 5, 50)

#### Example 2: Saddle Point

```
Equation: x^2 - y^2
Optimize: y
Start X: 1
Start Y: 1
Learning Rate: 0.01
```

**Expected Result**: May not converge - saddle point at (0, 0)

#### Example 3: Complex Surface

```
Equation: sin(x) + cos(y) + 0.1*x^2 + 0.1*y^2
Optimize: y
Start X: 3
Start Y: 3
Learning Rate: 0.05
```

**Expected Result**: Finds one of multiple local minima

---

## Advanced Topics

### 1. Numerical Stability

#### Finite Difference Errors

**Truncation Error**: Using finite h introduces approximation error
```
Error ≈ h² * |f'''(x)| / 6
```

**Roundoff Error**: Computer arithmetic is not exact
```
Roundoff ≈ ε / h
```

**Optimal h**: Balance truncation and roundoff
```
h_optimal ≈ (3ε)^(1/3) ≈ 10^(-5) to 10^(-4)
```

We use `h = 0.0001` as a compromise.

#### Hessian Singularity

At saddle points: `det(H) ≈ 0`

**Solution**: Check determinant before inversion
```cpp
if (abs(det) < 1e-10) {
    // Fall back to gradient descent or terminate
}
```

### 2. Optimization Challenges

#### Local vs Global Minima

**Problem**: Gradient-based methods find local minima, not necessarily global

**Solutions**:
- Multiple random starts
- Simulated annealing
- Genetic algorithms

#### Plateau Regions

**Problem**: ||∇f|| ≈ 0 but not at minimum

**Detection**:
```cpp
if (gradMag < tolerance && iterations < maxIterations/2) {
    // Might be on plateau, not at minimum
}
```

#### Oscillation in Narrow Valleys

**Problem**: Learning rate too large for valley width

**Solution**: Adaptive learning rate (momentum, Adam optimizer)

### 3. Performance Optimization

#### Mesh Generation

**Current**: O(n²) evaluations for n×n grid

**Optimization**: Adaptive mesh refinement
- Use coarse mesh far from interesting regions
- Refine near steep gradients or minima

#### Rendering

**Current**: Redraw entire mesh every frame

**Optimizations**:
- Display lists (pre-compiled geometry)
- Vertex Buffer Objects (VBO) for GPU storage
- Level of Detail (LOD) based on camera distance

### 4. Mathematical Extensions

#### Constrained Optimization

**Problem**: Minimize f(x, y) subject to g(x, y) = 0

**Method**: Lagrange multipliers
```
L(x, y, λ) = f(x, y) + λ·g(x, y)
∇L = 0
```

#### Multi-variable Optimization

**Extension**: Optimize functions of n variables

**Changes Needed**:
- n-dimensional gradient
- n×n Hessian matrix
- Matrix inversion using LU decomposition

#### Quasi-Newton Methods

**BFGS Algorithm**: Approximates Hessian instead of computing it
- Faster than full Newton
- More robust than gradient descent

### 5. GPU Acceleration

#### Parallel Surface Evaluation

```cpp
// Pseudocode for CUDA/OpenCL
kernel evaluateSurface(float* x, float* y, float* z, int n) {
    int i = get_global_id(0);
    if (i < n) {
        z[i] = f(x[i], y[i]);  // Each thread evaluates one point
    }
}
```

**Speedup**: 10-100x for large meshes

#### GPU-Based Rendering

Modern approach: Vertex shaders compute surface on GPU
```glsl
// GLSL vertex shader
void main() {
    float z = x*x + y*y;  // Evaluate surface
    gl_Position = projectionMatrix * viewMatrix * vec4(x, y, z, 1.0);
}
```

### 6. Extending the Parser

#### Adding Custom Functions

```cpp
// In EquationParser constructor:
functions["sigmoid"] = [](double x) { 
    return 1.0 / (1.0 + exp(-x)); 
};

functions["relu"] = [](double x) { 
    return max(0.0, x); 
};
```

#### Variable Substitution

```cpp
// Allow user-defined variables
parser.setVariable("a", 2.0);
parser.setVariable("b", 3.0);
// Now equation "a*x + b*y" evaluates with a=2, b=3
```

#### Symbolic Differentiation

**Current**: Numerical derivatives

**Advanced**: Parse equation into expression tree, apply differentiation rules

```
d/dx(x²) = 2x
d/dx(sin(x)) = cos(x)
d/dx(f+g) = f' + g'
d/dx(f*g) = f'g + fg'
```

---

## Code Organization Best Practices

### Header Guards

```cpp
#ifndef SURFACE_H
#define SURFACE_H
// ... declarations ...
#endif
```

**Why?** Prevents multiple inclusion in compilation units.

### Const Correctness

```cpp
double evaluate(double x, double y) const;  // Doesn't modify object
```

**Benefits**:
- Compiler optimization
- Self-documenting code
- Catch accidental modifications

### RAII (Resource Acquisition Is Initialization)

```cpp
std::unique_ptr<Surface> surface;  // Automatic memory management
```

**No manual delete needed** - destructor automatically called.

### Separation of Concerns

Each class has a **single responsibility**:
- `Surface`: Mathematical function representation
- `Optimizer`: Finding minima
- `Visualizer`: 3D rendering
- `EquationParser`: String → function
- `GUIManager`: User interface orchestration

---

## Troubleshooting

### Common Build Errors

#### "FreeGLUT not found"

**Linux**: `sudo apt-get install freeglut3-dev`

**Windows**: Download from freeglut.sourceforge.net, set `FREEGLUT_DIR`

#### "GL/glut.h: No such file"

Check include paths in CMakeLists.txt:
```cmake
include_directories(${FREEGLUT_DIR}/include)
```

### Runtime Errors

#### "Singular Hessian"

**Cause**: At saddle point or flat region

**Solution**: Try different starting point or use gradient descent

#### "Division by zero"

**Cause**: Parsing `1/0` or surface that divides by zero

**Solution**: Validate equation, check domain

#### Surface not rendering

**Possible causes**:
- Domain doesn't contain surface (all z values are NaN/Inf)
- Resolution too high for memory
- OpenGL context not initialized

---

## Future Enhancements

### Planned Features

1. **More Optimization Algorithms**
   - Adam optimizer
   - L-BFGS
   - Conjugate gradient

2. **Better Visualization**
   - Color mapping (heat map)
   - Contour lines
   - Multiple optimization paths

3. **Advanced Parser**
   - Symbolic differentiation
   - Expression simplification
   - Multi-line equations

4. **User Interface**
   - Modern GUI (Qt/ImGui)
   - Real-time equation editing
   - Parameter sliders

5. **Export Capabilities**
   - Save surfaces as OBJ files
   - Export optimization data to CSV
   - Screenshot functionality

### Contributing

This project follows standard C++ coding conventions:
- CamelCase for classes
- camelCase for methods
- UPPER_CASE for constants
- Meaningful variable names
- Comments for complex algorithms

---

## References & Further Reading

### Books

1. **"Numerical Optimization"** by Nocedal & Wright
   - Comprehensive optimization theory
   - Convergence proofs
   - Advanced algorithms

2. **"Computer Graphics: Principles and Practice"** by Foley et al.
   - OpenGL fundamentals
   - Lighting models
   - Rendering techniques

3. **"Compilers: Principles, Techniques, and Tools"** (Dragon Book)
   - Parser theory
   - Recursive descent parsing
   - Abstract syntax trees

### Online Resources

- **OpenGL Tutorial**: learnopengl.com
- **CMake Documentation**: cmake.org/documentation
- **C++ Reference**: cppreference.com
- **Optimization Algorithms**: Wikipedia articles on gradient descent, Newton's method

### Mathematical Background

- **Calculus**: Multivariable calculus, partial derivatives
- **Linear Algebra**: Matrices, eigenvalues, positive definiteness
- **Numerical Methods**: Finite differences, iterative methods

---

## License & Credits

### Project Information

- **Author**: Created as an educational project
- **Purpose**: Demonstrating optimization algorithms and 3D visualization
- **License**: Open source (specify license)

### Technologies Used

- **C++17**: Core language
- **OpenGL**: 3D graphics API
- **FreeGLUT**: Window management and input
- **CMake**: Build system

### Acknowledgments

- FreeGLUT developers for the OpenGL toolkit
- The C++ community for std::function and modern C++ features
- Mathematical optimization community for algorithm research

---

## Appendix: Complete Mathematical Formulation

### Problem Statement

Given a continuous function `f: ℝ² → ℝ`, find:

```
x* = argmin f(x, y)
     (x,y)∈D
```

Where D is the domain (rectangular region).

### Gradient Descent Formulation

**Initialize**: `x₀ = (x₀, y₀)`

**Iterate**: For `t = 0, 1, 2, ...`
```
x(t+1) = x(t) - α∇f(x(t))
```

**Stop**: When `||∇f(x(t))|| < ε`

**Convergence**: If f is L-smooth and α < 1/L:
```
f(x(k)) - f(x*) ≤ (L||x₀ - x*||²) / (2k)
```

### Newton's Method Formulation

**Initialize**: `x₀ = (x₀, y₀)`

**Iterate**: For `t = 0, 1, 2, ...`
```
x(t+1) = x(t) - [H(x(t))]⁻¹∇f(x(t))
```

Where:
```
H = [ ∂²f/∂x²    ∂²f/∂x∂y ]
    [ ∂²f/∂x∂y   ∂²f/∂y²  ]
```

**Convergence**: If f is strongly convex and starting point close enough:
```
||x(k+1) - x*|| ≤ M||x(k) - x*||²
```

Quadratic convergence rate!

---

## Appendix: Code Statistics

### Lines of Code

```
Point3D.h/cpp:         ~100 lines
Surface.h/cpp:         ~200 lines
Optimizer.h/cpp:       ~250 lines
Visualizer.h/cpp:      ~350 lines
EquationParser.h/cpp:  ~600 lines
GUIManager.h/cpp:      ~800 lines
main*.cpp:             ~100 lines
Total:                 ~2400 lines
```

### Complexity Analysis

**Surface Evaluation**: O(1) per point

**Gradient Computation**: O(1) (4 function evaluations)

**Hessian Computation**: O(1) (9 function evaluations)

**Mesh Generation**: O(n²) for n×n grid

**Optimization**: O(k·m) where k = iterations, m = cost per iteration

**Parsing**: O(n) where n = equation length

---

This README provides a comprehensive technical overview of the 3D Surface Optimizer project. For specific questions or contributions, please refer to the individual source files and their inline documentation.

**Happy Optimizing! 🎯**