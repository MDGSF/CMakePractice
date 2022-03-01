cmake_minimum_required(VERSION 3.5) # 设置 CMake 最小版本

project(cg) # 设置工程名

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(vendor/assimp)
# add_subdirectory(vendor/FreeImage)
# add_subdirectory(vendor/FreeType)
# add_subdirectory(vendor/GLAD)
# add_subdirectory(vendor/GLEW)
# add_subdirectory(vendor/GLFW)
# add_subdirectory(vendor/glm)
# add_subdirectory(vendor/Pango)
add_subdirectory(cgutils)
add_subdirectory(subbinary)
