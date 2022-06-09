cmake_minimum_required(VERSION 3.0.0)
project(cmaketest VERSION 0.1.0)

include_directories("${PROJECT_BINARY_DIR}")
#…Ë÷√ø‚
file( GLOB LIB_SOURCES ../../Include/*.cpp )
file( GLOB LIB_HEADERS ../../Include/*.h )
add_library( YourLib ${LIB_SOURCES} ${LIB_HEADERS} )
#ƒ£ Ω£∫DEBUG
SET(EXECUTABLE_OUTPUT_PATH ../bin)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug")
INCLUDE_DIRECTORIES(../../Include/)
# Find all main*.cpp files and store in list mains
file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(mainfile IN LISTS mains)
    # Get file name without directory
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    target_link_libraries( ${mainname} YourLib )

endforeach()

    execute_process(COMMAND ../../bin/main.exe)