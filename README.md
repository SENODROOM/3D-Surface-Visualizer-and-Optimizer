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