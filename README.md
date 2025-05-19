# About
Simple text to number parser library as a hobby thing.

# Installation
Clone the repo:
```
git clone https://github.com/z0rhan/t2n.git
```
You must have Git and CMake installed in your system.   
Then run:
```
mkdir build
cd build
cmake ..
make
```
Now a static library is generated inside lib/.

# Usage
To use the library, copy:
- `build/lib/` (Contains the static library)
- `include/`   (Contains the header files)

to your project folder and link them in your build system.   
Use `#include <t2n.hh>` in your file to include the header file.
