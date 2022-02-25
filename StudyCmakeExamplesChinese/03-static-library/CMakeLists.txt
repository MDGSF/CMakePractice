cmake_minimum_required(VERSION 3.5) # 设置 CMake 最小版本

project(hello_library) # 设置工程名

############################################################
# Create a library
############################################################

# 库的源文件 Hello.cpp 生成静态库 hello_library
add_library(hello_library STATIC
  src/Hello.cpp
)

# target_include_directories 为一个目标（可能是一个库 library 也可能是可执行文件）
# 添加头文件路径。
# 使用这个函数后，这个目录会在以下情况被调用：
#   1. 编译这个库的时候
#   2. 编译链接到这个库hello_library的任何其他目标（库或者可执行文件）
target_include_directories(hello_library
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################
# Add an executable with the above sources
# 指定用哪个源文件生成可执行文件
add_executable(hello_binary
  src/main.cpp
)

# 链接可执行文件和静态库
target_link_libraries(hello_binary
  PRIVATE
  hello_library
)
