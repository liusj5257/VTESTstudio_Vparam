cmake_minimum_required(VERSION 3.0.0)
project(cmaketest VERSION 0.1.0)

# Enable C++11
add_compile_options(-std=c11 -v)

# 设置exe输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 设置静态lib输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 模式：DEBUG
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include/)

# 设置库路径
file(GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.c)
file(GLOB LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)

# add_library(YourLib SHARED ${LIB_SOURCES} ${LIB_HEADERS} )#动态dll
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(lib_MY SHARED ${LIB_SOURCES} ${LIB_HEADERS})
set_target_properties(
  lib_MY PROPERTIES OUTPUT_NAME "_MY" RUNTIME_OUTPUT_DIRECTORY
                                      ${CMAKE_SOURCE_DIR}/bin)

# 添加CMAKE子目录
add_subdirectory(Include)

# 库变量
find_library(static_lib lib_MY ${CMAKE_SOURCE_DIR}/lib)

# Find all main*.cpp files and store in list mains
file(
  GLOB_RECURSE mains
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Source/**/"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/**/*.c")

# 要先生成lib再添加下方代码
foreach(mainfile IN LISTS mains)
  # Get file name without directory
  get_filename_component(mainname ${mainfile} NAME_WE)
  add_executable(${mainname} ${CMAKE_CURRENT_SOURCE_DIR}/Source/**/${mainfile})
  target_link_libraries(${mainname} ${static_lib})
  add_dependencies(${mainname} lib_MY)
endforeach()
