# Game2048

This is a simple text implementation of the game "2048".

### For compilation you need:
* A recent version of gcc (tested with v.4.8.1)
* Cmake (tested with v. 2.8.11.2)
* The google test library (tested with v. 1.6.0-4.1.2)
* Doxygen (tested with v. 1.8.5)

### Compile instructions:
(in source directory)
* mkdir build
* cd build
* cmake [-Dbuild_test=ON/OFF"] [-Dbuild_doc=ON/OFF"] ../
* make

#### Cmake options:
* -Dbuild_test=ON/OFF = Whether to build unit tests - The GTEST_ROOT environment variable should point to the location of the directory containing libgtest.a, if it is not installed in the usual system directories.
* -Dbuild_doc=ON/OFF = Whether to build doxygen API documentation

#### Build API docs:
* make doc

#### Run tests:
Either 
* ./runtests (native)
or
* make test (CTest)
