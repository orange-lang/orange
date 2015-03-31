include_directories(${CMAKE_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/river RIVER_SOURCES) 

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(river ${RIVER_SOURCES} ${INCLUDES})
target_link_libraries(river helper)

install(TARGETS river DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)