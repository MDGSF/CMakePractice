#!/usr/bin/env bash
mkdir build
cd build

# 在命令行运行 cmake 的时候
# 使用 cmake 命令行的 -D 选项配置编译类型
cmake .. -DCMAKE_BUILD_TYPE=Release

# 仅输出构建状态
make

# 输出详细日志
# make VERBOSE=1

