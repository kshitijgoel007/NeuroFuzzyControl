# NeuroFuzzyControl
Software package development for assignments during the course AE51021 Neuro-Fuzzy Control.
- This repository follows [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- This repository uses the `cmake` build system.

### Online Neural Network for predicting Daily Sun Spot Number
Implementation of Multilayer Feed Forward Network which is able to fit time-series Sun Spot Number using the data available at [SIDC, Belgium](www.sidc.be/silso/datafiles).

Current implementation capabilities:
- Any kind of user-defined topology definition.
- Backpropogation training.
- Windowing dataset for time-series based regression.
- Plotting using `numpy` and `matplotlib`.

Instructions:
1. Make a build directory. `mkdir build`.
2. Run `cmake ..` in the build directory.
3. Run `make` inside the build directory.
4. Switch to the parent directory and run `chmod +x run.sh`.
5. Finally, `./run.sh` in the parent directory.
6. Input the net topology and number of epochs.
7. The project should look like this finally on a linux system:
```
.
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.6.0
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeSystem.cmake
│   │   │   ├── CompilerIdC
│   │   │   │   ├── a.out
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   └── CompilerIdCXX
│   │   │       ├── a.out
│   │   │       └── CMakeCXXCompilerId.cpp
│   │   ├── cmake.check_cache
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── CMakeTmp
│   │   ├── feature_tests.bin
│   │   ├── feature_tests.c
│   │   ├── feature_tests.cxx
│   │   ├── Makefile2
│   │   ├── Makefile.cmake
│   │   ├── neuralNet.dir
│   │   │   ├── build.make
│   │   │   ├── cmake_clean.cmake
│   │   │   ├── CXX.includecache
│   │   │   ├── DependInfo.cmake
│   │   │   ├── depend.internal
│   │   │   ├── depend.make
│   │   │   ├── flags.make
│   │   │   ├── link.txt
│   │   │   ├── progress.make
│   │   │   └── src
│   │   │       ├── main.cpp.o
│   │   │       ├── net.cpp.o
│   │   │       ├── neuron.cpp.o
│   │   │       └── parser.cpp.o
│   │   ├── progress.marks
│   │   └── TargetDirectories.txt
│   ├── cmake_install.cmake
│   ├── Makefile
│   └── neuralNet
├── CMakeLists.txt
├── Data
│   ├── SN_Monthly2.txt
│   ├── SN_MONTHLY.txt
│   └── SN_YEARLY.txt
├── helper_files
│   └── plotting.py
├── include
│   ├── gnuplot_i.hpp
│   ├── net.h
│   ├── neuron.h
│   └── parser.h
├── LICENSE
├── output_data
│   ├── desired.txt
│   ├── input.txt
│   ├── MSE_test.txt
│   ├── MSE.txt
│   └── results.txt
├── README.md
├── run.sh
└── src
    ├── main.cpp
    ├── net.cpp
    ├── neuron.cpp
    └── parser.cpp
```

### Dynamic Neural Units based control of satellites.
TODO:
- Real-time plotting using an appropriate plotting tool.
- Recurrent Neural Net implentation.
- Dynamic Neural Net implementation for Satellite Control.
