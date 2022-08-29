add_library(lib_MY SHARED ${LIB_SOURCES} ${LIB_HEADERS})
set_target_properties(
  lib_MY PROPERTIES OUTPUT_NAME "_MY" RUNTIME_OUTPUT_DIRECTORY
                                      ${CMAKE_SOURCE_DIR}/bin)

# add_library(YourLib ${LIB_SOURCES} ${LIB_HEADERS} )
# set_target_properties(YourLib PROPERTIES OUTPUT_NAME "_MY")
