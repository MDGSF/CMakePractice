#!/usr/bin/env bash
mkdir build
cd build

clang_bin=`which clang`
clang_xx_bin=`which clang++`
cmake \
  .. \
  -DCMAKE_C_COMPILER=$clang_bin \
  -DCMAKE_CXX_COMPILER=$clang_xx_bin \
  -DCMAKE_BUILD_TYPE=Release

make
# make VERBOSE=1
