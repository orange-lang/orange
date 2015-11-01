include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/cmd CMD_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_library(cmd ${CMD_SOURCES} ${INCLUDES})
target_link_libraries(cmd)
