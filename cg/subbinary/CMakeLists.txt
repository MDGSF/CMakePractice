project(subbinary) # 设置工程名

add_executable(${PROJECT_NAME} main.cpp) # 生成可执行文件


# cgutils
target_link_libraries(${PROJECT_NAME} cgutils)


# assimp, 头文件在 vendor/assimp/assimp-5.2.2/include/assimp 下面
include_directories(vendor/assimp/assimp-5.2.2/include/)
target_link_libraries(${PROJECT_NAME} assimp)


# glm, 头文件在 vendor/glm/glm-0.9.9.8/glm 下面
include_directories(vendor/glm/glm-0.9.9.8)


# glad2, 头文件在 vendor/GLAD/glad2_gles3.2_headeronly/include/glad 下面
include_directories(vendor/GLAD/glad2_gles3.2_headeronly/include)


# glfw, 头文件在 vendor/GLFW/glfw-3.3.6/include/GLFW 下面
include_directories(vendor/GLFW/glfw-3.3.6/include)
target_link_libraries(${PROJECT_NAME} glfw)

