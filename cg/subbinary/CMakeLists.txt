project(subbinary) # 设置工程名

add_executable(${PROJECT_NAME} main.cpp) # 生成可执行文件

# assimp
include_directories(vendor/assimp/assimp-5.2.2/include/)
target_link_libraries(${PROJECT_NAME} assimp)
