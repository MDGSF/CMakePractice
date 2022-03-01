project(cgutils) # 设置工程名

if(${BUILD_SHARED_LIBS})
  set(BUILD_LIB_TYPE SHARED)
else()
  set(BUILD_LIB_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${BUILD_LIB_TYPE} cgutils.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

# assimp, 头文件在 vendor/assimp/assimp-5.2.2/include/assimp 下面
include_directories(vendor/assimp/assimp-5.2.2/include/)
target_link_libraries(${PROJECT_NAME} assimp)

# glm, 头文件在 vendor/glm/glm-0.9.9.8/glm 下面
include_directories(vendor/glm/glm-0.9.9.8)
