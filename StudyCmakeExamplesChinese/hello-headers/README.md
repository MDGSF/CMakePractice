# hello-cmake

## 常用变量

- **PROJECT_NAME**: 工程名字，project() 执行的时候，会生成该变量
- **PROJECT_SOURCE_DIR**：工程顶层目录
- **PROJECT_BINARY_DIR**：暂认为就是 **CMAKE_BINARY_DIR**

- **CMAKE_SOURCE_DIR**：根源代码目录，工程顶层目录。暂认为就是 **PROJECT_SOURCE_DIR**
- **CMAKE_BINARY_DIR**：运行 cmake 的目录。外部构建时就是 build 目录。
- **CMAKE_CURRENT_SOURCE_DIR**：当前处理的 CMakeLists.txt 所在的路径
- **CMAKE_CURRENT_BINARY_DIR**：The build directory you are currently in，当前所在 build 目录

可以在 CMakeLists.txt 中，利用 message() 命令输出一下这些变量。
这些变量不仅可以在 CMakeLists.txt 中使用，同样可以在源代码 cpp 中使用。

对于 Modern CMake，不建议对源文件使用变量。不建议使用 glob。
通常直接在 `add_xxx` 函数中声明源文件。
