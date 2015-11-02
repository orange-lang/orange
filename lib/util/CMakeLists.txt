include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/util UTIL_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/util/*.h")

add_library(util ${UTIL_SOURCES} ${INCLUDES})
cotire(util)
target_link_libraries(util)
