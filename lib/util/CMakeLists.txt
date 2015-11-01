include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/util UTIL_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_library(util ${UTIL_SOURCES} ${INCLUDES})
target_link_libraries(util)
