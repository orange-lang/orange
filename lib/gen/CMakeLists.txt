# LLVM stuff
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs native core)

find_package(BISON REQUIRED)
bison_target(BisonOutput ${gen_SOURCE_DIR}/parser.y ${gen_SOURCE_DIR}/parser.cc COMPILE_FLAGS "-d")

find_package(FLEX REQUIRED)
flex_target(FlexOutput ${gen_SOURCE_DIR}/lexer.l ${gen_SOURCE_DIR}/lexer.cc)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${gen_SOURCE_DIR} GEN_SOURCES)

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_library (gen 
	${GEN_SOURCES} ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS} ${INCLUDES}
)

target_link_libraries(gen ${llvm_libs})