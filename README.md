# nanofetch
Nanofetch is a very simple CLI hardware info fetcher, written in C++. 
![Image](https://github.com/MrCheatEugene/nanofetch/blob/main/image.jpg?raw=true)

# Quick Start
If you don't know how to build c++ code, then just download nanofetch.exe&libcpuid.dll from the main branch or install DPKG file and run 'nanofetch' in terminal.

Below is a guide for advanced users, who want to modify sysinfo.
# How to build?

1. Install G++ on Linux or TDM-GCC on Windows(and if you're on windows - install libcpuid, for linux - you don't need it - it is included already)
2. For windows, the compilation command is this:
```
g++.exe "sysinfo.cpp" -o "sysinfo.exe"  -I"TDM-GCC-64\include" -I"TDM-GCC-64\x86_64-w64-mingw32\include" -I"TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\9.2.0\include" -I"TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\9.2.0\include\c++" -L"TDM-GCC-64\lib" -L"TDM-GCC-64\x86_64-w64-mingw32\lib" -lcpuid -static-libgcc
```
I've removed local paths that were used by Dev C++(I used it for writing and compiling sysinfo on Windows), but if you are having problems building - here is the original command:
```
g++.exe "C:\Users\user\Documents\sysinfo\sysinfo.cpp" -o "C:\Users\user\Documents\sysinfo\sysinfo.exe"  -I"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\include" -I"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\x86_64-w64-mingw32\include" -I"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\9.2.0\include" -I"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\9.2.0\include\c++" -L"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\lib" -L"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\x86_64-w64-mingw32\lib" -lcpuid -static-libgcc
```

Compiler name: TDM-GCC 9.2.0 64-bit Release

3. For Linux, compilation command is this:
```
g++ sysinfo.cpp -o mysysinfo -I ./incl-libs/ -L ./incl-libs/ -lcpuid 
```
Incl-libs directory is avaliable in repository's main branch.

Also, you need to install libcpuid library using APT/DPKG/Pacman. DPKG package is avaliable in repository's main branch.
# How to use?

Just run sysinfo.exe(the libcpuid.dll must be near sysinfo.exe) or ./mysysinfo.
Also, you need to install libcpuid library (if you use Linux) using APT/DPKG/Pacman. DPKG package is avaliable in repository's main branch.
# Supported Operating Systems
SysInfo supports almost all linux distros and unix-based OS's. And also Windows.

But, on unknown hardware some things may not be correct.
