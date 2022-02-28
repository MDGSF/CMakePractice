#!/usr/bin/env bash

mkdir build

cd build

cmake \
  ../assimp-5.2.2 \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON

make -j4

# 输出详细日志
# make VERBOSE=1
