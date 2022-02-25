# compile flags

- C++编译标志: `CMAKE_CXX_FLAGS`
- C语言编译标志: `CMAKE_C_FLAGS`
- 设置链接标志: `CMAKE_LINKER_FLAGS`

```sh
cmake .. -DCMAKE_CXX_FLAGS="-DEX3"
```

首选使用 `target_compile_definitions` 函数

