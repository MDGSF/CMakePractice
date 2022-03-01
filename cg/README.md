# cg template

## Ubuntu 18.04

```sh
sudo apt-get install -y libxrandr-dev
sudo apt-get install -y libxinerama-dev
sudo apt-get install -y libxcursor-dev
sudo apt-get install -y libxi-dev
```

## Windows

```sh
cmake.exe -G"Visual Studio 16 2019" -H. -Bbuild -T host=x86 -A x64
cmake.exe --build build --config Release
```
