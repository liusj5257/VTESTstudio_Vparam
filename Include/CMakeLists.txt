add_library(YourLib SHARED ${LIB_SOURCES} ${LIB_HEADERS} )#¶¯Ì¬dll
set_target_properties(YourLib PROPERTIES OUTPUT_NAME "_MY" RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


#add_library(YourLib ${LIB_SOURCES} ${LIB_HEADERS} )
#set_target_properties(YourLib PROPERTIES OUTPUT_NAME "_MY")


