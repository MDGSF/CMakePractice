#!/usr/bin/bash

OPENCV_SOURCE_HOME=/home/huangjian/opt/opencv/opencv-4.5.5/opencv-4.5.5
OPENCV_CONTRIB_SOURCE_HOME=/home/huangjian/opt/opencv/opencv_contrib-4.5.5/opencv_contrib-4.5.5

mkdir build
cd build

cmake \
  -DCMAKE_INSTALL_PREFIX=/home/huangjian/opt/opencv/opencv-4.5.5-binary \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DBUILD_DOCS=OFF \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_TESTS=OFF \
  -DBUILD_PERF_TESTS=OFF \
  -DOPENCV_EXTRA_MODULES_PATH=$OPENCV_CONTRIB_SOURCE_HOME/modules \
  $OPENCV_SOURCE_HOME

make -j8

