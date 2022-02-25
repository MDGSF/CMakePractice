#!/usr/bin/env bash

mkdir build

cd build

cmake \
  .. \
  -DCMAKE_BUILD_TYPE=Release

make

# 输出详细日志
# make VERBOSE=1
