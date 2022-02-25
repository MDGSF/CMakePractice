project(sublibrary2)

# 如果您有一个库被创建为仅头文件的库，则 cmake 支持 INTERFACE 目标，
# 以允许创建没有任何构建输出的目标。
add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  INTERFACE
  ${PROJECT_SOURCE_DIR}/include
)
