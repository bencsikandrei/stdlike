# Std-like algorithms and abstractions

Found myself needing some things I was unable to find in the stl or boost. For those occasions I created a repo for gathering my work.

If some of these become obsolete one day because of the inclusion in the standard (or boost) then great.

# Building

Simple CMake setup. Create a build directory and do a make help to see the targets. Or just build all.

```bash
mkdir build && cd build
cmake ../
make -j all 
```

# Enabling and running tests

Uses Ctest as a runner and Gtest for UTs.
To enable testing you need to run cmake with -DENABLE_TESTING=ON

```bash
mkdir build && cd build
cmake -DENABLE_TESTING=ON ../
make -j libtest
ctest 
```