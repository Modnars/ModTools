###
 # @Author: modnarshen
 # @Date: 2022/05/12 15:07:54
 # @LastEditors: modnarshen
 # @Description: 
### 
#!/usr/bin/env bash

BUILD_DIR="build/"

mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ..
make -j10
