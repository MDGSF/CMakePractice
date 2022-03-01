#!/usr/bin/env bash

if [ ! -d "build" ]; then
  mkdir build
fi
cd build

cmake \
  .. \
  -DCMAKE_BUILD_TYPE=Release

make -j4

# 输出详细日志
# make VERBOSE=1
