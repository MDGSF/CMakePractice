# CMakePractice

## cmake 常用参数

```text
# 使用 4 个 CPU 编译
-j4

# 设置编译目录
-Bbuild

# 设置 CMakeLists.txt 目录
-H.

# 设置编译类型
-DCMAKE_BUILD_TYPE=Release / Debug

# 设置是否开启动态库编译
-DBUILD_SHARED_LIBS=ON / OFF

# 设置 C 语言编译工具链
-DCMAKE_C_COMPILER=/home/huangjian/xxx/aarch64-linux-android-clang
```

## Windows 下使用

```sh
cmake.exe -G"Visual Studio 16 2019" -H<source_dir> -B<build_dir>
cmake.exe -G"Visual Studio 16 2019" -H. -BBuild

cmake.exe --build Build
cmake.exe --build Build --config Debug|Release


cmake.exe -G"Visual Studio 16 2019" -H. -BBuild -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} /wd4819 /wd4530"
cmake.exe --build Build --config Release
```

```sh
Visual Studio 17 2022
Visual Studio 16 2019
Visual Studio 15 2017
Visual Studio 14 2015
Visual Studio 12 2013
Visual Studio 11 2012
Visual Studio 10 2010
Visual Studio 9 2008
```

```sh
https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=msvc-170
/w       Suppresses all compiler warnings.
/W0      Suppresses all warnings. It's equivalent to /w.
/W1      Displays level 1 (severe) warnings. /W1 is the default setting in the command-line compiler.
/W2
/W3
/W4
/Wall
/WX      Treats all compiler warnings as errors.
/WX-     和 /WX 相反
/wdnnnn  Suppresses the compiler warning that is specified by nnnn.
         For example, /wd4326 suppresses compiler warning C4326.
```

## resources 资源

https://github.com/onqtam/awesome-cmake
https://github.com/Akagi201/learning-cmake
https://github.com/ttroy50/cmake-examples
https://github.com/SFUMECJF/cmake-examples-Chinese
https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1

