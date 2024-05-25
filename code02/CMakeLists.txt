cmake_minimum_required(VERSION 3.15)
project(project LANGUAGES C CXX)

#set(SRC test.cpp)
#aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#[[
file(GLOB SRCLIB ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
]]#
#[[
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
]]#
#[[
# 生成静态库
add_library(extnum STATIC ${SRCLIB})
]]#

set(EXECUTABLE_OUTPUT_PATH /home/guangying/code/code02/output)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)


# 包含静态库路径
#link_directories(${PROJECT_SOURCE_DIR}/lib)
#[[
# 链接静态库
link_libraries(extnum)
]]#

add_executable(app ${SRC})

#target_link_libraries(app extnum)

target_link_libraries(app csapp)

set_target_properties(app PROPERTIES LINKER_LANGUAGE CXX)