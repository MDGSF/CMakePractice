project(Breakout) # 设置工程名

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lX11 -lpthread -lXrandr -lXi -ldl")
SET(CMAKE_CXX_FLAGS_DEBUG   "-std=c++11 -Wall -Wno-unused-local-typedefs -Wno-unused-function -fPIC -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -Wno-unused-local-typedefs -Wno-unused-function -fPIC -O3")


add_executable(${PROJECT_NAME}
  main.cpp
  shader.cpp
  sprite_renderer.cpp
  stb_image.cpp
  texture.cpp
  ${CMAKE_SOURCE_DIR}/vendor/GLAD/glad1_gl4.6/src/glad.c
) # 生成可执行文件


# cgutils
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/cgutils
)
target_link_libraries(${PROJECT_NAME} cgutils)


# assimp, 头文件在 vendor/assimp/assimp-5.2.2/include/assimp 下面
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/assimp/assimp-5.2.2/include/
)
target_link_libraries(${PROJECT_NAME} assimp)


# glm, 头文件在 vendor/glm/glm-0.9.9.8/glm 下面
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/glm/glm-0.9.9.8
)


# glad2, 头文件在 vendor/GLAD/glad2_gles3.2_headeronly/include/glad 下面
# target_include_directories(${PROJECT_NAME}
#   PRIVATE
#   ${CMAKE_SOURCE_DIR}/vendor/GLAD/glad2_gles3.2_headeronly/include
# )


# glad1
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/GLAD/glad1_gl4.6/include
)


# glfw, 头文件在 vendor/GLFW/glfw-3.3.6/include/GLFW 下面
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/GLFW/glfw-3.3.6/include
)
target_link_libraries(${PROJECT_NAME} glfw)


# freeimage, 头文件和库都在目录 vendor/FreeImage/freeimage-3.18.0_ubuntu1804_gcc7.5.0 下面
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/FreeImage/freeimage-3.18.0_ubuntu1804_gcc7.5.0
)
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/vendor/FreeImage/freeimage-3.18.0_ubuntu1804_gcc7.5.0/libfreeimage.so
)


# freetype, 头文件在目录 vendor/FreeType/freetype-2.11.1_ubuntu1804_gcc7.5.0/include/freetype2 下面
# freetype, 库在目录 vendor/FreeType/freetype-2.11.1_ubuntu1804_gcc7.5.0/lib 下面
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/FreeType/freetype-2.11.1_ubuntu1804_gcc7.5.0/include/freetype2
)
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/vendor/FreeType/freetype-2.11.1_ubuntu1804_gcc7.5.0/lib/libfreetype.so
)


# stb
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/stb/stb_20220301
)


target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

