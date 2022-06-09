cmake_minimum_required(VERSION 3.0.0)
project(cmaketest VERSION 0.1.0)


#����exe���Ŀ¼
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#���þ�̬lib���Ŀ¼
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)


#ģʽ��DEBUG
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Include/)


#���ÿ�·��
file( GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.cpp )
file( GLOB LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h )
#add_library(YourLib SHARED ${LIB_SOURCES} ${LIB_HEADERS} )#��̬dll


# ����CMAKE��Ŀ¼
add_subdirectory(Include)

#�����
find_library(static_lib lib_MY ${CMAKE_SOURCE_DIR}/lib)

# Find all main*.cpp files and store in list mains
file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Source/**/" "${CMAKE_CURRENT_SOURCE_DIR}/Source/**/*.cpp")
foreach(mainfile IN LISTS mains)
# Get file name without directory
get_filename_component(mainname ${mainfile} NAME_WE)
add_executable(${mainname} ${CMAKE_CURRENT_SOURCE_DIR}/Source/**/${mainfile})
target_link_libraries( ${mainname} ${static_lib})
endforeach()