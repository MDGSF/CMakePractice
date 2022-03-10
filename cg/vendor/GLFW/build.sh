#!/usr/bin/env bash

mkdir -p build
cd build

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  ..

make -j4

# 输出详细日志
# make VERBOSE=1
