#!/usr/bin/env bash

cmake \
  -B build \
  -S glfw-3.3.6 \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON

make -j4

# 输出详细日志
# make VERBOSE=1
