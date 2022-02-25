# build type

## 优化级别

- Release —— 不可以打断点调试，程序开发完成后发行使用的版本，占的体积小。
    它对代码做了优化，因此速度会非常快，
    在编译器中使用命令： -O3 -DNDEBUG 可选择此版本。
- Debug ——调试的版本，体积大。
    在编译器中使用命令： -g 可选择此版本。
- MinSizeRel—— 最小体积版本
    在编译器中使用命令：-Os -DNDEBUG可选择此版本。
- RelWithDebInfo—— 既优化又能调试。
    在编译器中使用命令：-O2 -g -DNDEBUG可选择此版本。

## set

- 正常变量
- CACHE变量
- 环境变量
