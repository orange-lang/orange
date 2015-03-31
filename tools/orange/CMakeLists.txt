include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange ORANGE_SOURCES) 

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(orange ${ORANGE_SOURCES} ${INCLUDES})
target_link_libraries(orange helper ${llvm_libs})
ADD_DEPENDENCIES(orange boot)

install(TARGETS orange DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)