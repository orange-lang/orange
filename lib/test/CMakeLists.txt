include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/test TEST_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/test/*.h")

add_library(testlib ${TEST_SOURCES} ${INCLUDES})
set_target_properties (testlib PROPERTIES FOLDER lib)
cotire(testlib)
target_link_libraries(testlib)
