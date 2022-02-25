#!/usr/bin/env bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release

# 仅输出构建状态
make

# 输出详细日志
# make VERBOSE=1

