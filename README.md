# Freestyle

Fork of http://freestyle.sourceforge.net modified to use the CMake build system and updated external libraries: Qt5, libQGLViewer 2.7, lib3ds 1.25, Python 2.7
Tested on macOS with Apple Clang (11) and GCC (9.3)

Known issue: 
- bug in SWIG generated wrapper file: remove extra spaces in operators `=  =` and `!  =`
