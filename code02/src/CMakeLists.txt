cmake_minimum_required(VERSION 3.15)
project(project LANGUAGES CXX)

#set(SRC test.cpp)
#aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
set(CMAKE_CXX_STANDARD 17)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

#file(GLOB SRCLIB ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp)
# 设置动态库/静态库生成路径
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)
# 生成静态库
#add_library(extnum STATIC ${SRCLIB})

#set_target_properties(extnum PROPERTIES LINKER_LANGUAGE CXX)