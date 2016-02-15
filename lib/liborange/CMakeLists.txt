find_package(LLVM REQUIRED HINTS
	${CMAKE_BINARY_DIR}/llvm_install/share/llvm/cmake
	${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs X86 ipo MCJIT)

include_directories(${CMAKE_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/liborange LIBORANGE_SOURCES)

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/liborange/*.h")

add_library(orange ${LIBORANGE_SOURCES} ${INCLUDES})
set_target_properties (orange PROPERTIES FOLDER lib)

target_link_libraries(orange ast util cmd parse ${llvm_libs})
add_dependencies(orange boot util cmd ast parse)
