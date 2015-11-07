find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs X86 ipo MCJIT)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib/util UTIL_SOURCES)
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/util/*.h")

add_library(util ${UTIL_SOURCES} ${INCLUDES})
cotire(util)
target_link_libraries(util ${llvm_libs})
