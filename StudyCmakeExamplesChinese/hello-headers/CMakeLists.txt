cmake_minimum_required(VERSION 3.5) # 设置 CMake 最小版本

project(hello_headers) # 设置工程名

# 创建一个变量，名字叫 SOURCES，它包含了所有的 cpp 文件。
set(SOURCES
  src/Hello.cpp
  src/main.cpp
)

# 用所有的源文件生成可执行文件 hello_headers
# 等价于 add_executable(hello_headers src/Hello.cpp src/main.cpp)
add_executable(hello_headers ${SOURCES})

# 设置这个可执行文件 hello_headers 需要包含的库的路径
target_include_directories(hello_headers
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

# PROJECT_SOURCE_DIR: 指工程顶层目录
# PROJECT_BINARY_DIR: 指编译目录
# PRIVATE: 指定了库的范围
