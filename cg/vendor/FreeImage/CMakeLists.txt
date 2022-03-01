project(freeimage)

if(${BUILD_SHARED_LIBS})
  set(BUILD_LIB_TYPE SHARED)
else()
  set(BUILD_LIB_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${BUILD_LIB_TYPE} IMPORTED)

message(STATUS "freeimage ---- ${PROJECT_SOURCE_DIR}/freeimage-3.18.0_ubuntu1804_gcc7.5.0")

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  IMPORTED_LOCATION
  ${PROJECT_SOURCE_DIR}/freeimage-3.18.0_ubuntu1804_gcc7.5.0
)
