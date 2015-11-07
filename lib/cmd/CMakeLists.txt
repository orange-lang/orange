include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/cmd CMD_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/cmd/*.h")

add_library(cmd ${CMD_SOURCES} ${INCLUDES})
set_target_properties (cmd PROPERTIES FOLDER lib)
cotire(cmd)
target_link_libraries(cmd)
