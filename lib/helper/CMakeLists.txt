include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/helper HELPER_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_library(helper ${HELPER_SOURCES} ${INCLUDES})
target_link_libraries(helper)
