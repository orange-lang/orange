cmake_minimum_required (VERSION 2.8.8)
project (oc)
set(oc_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tools/oc)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -O3 -Wno-deprecated-register")

# LLVM stuff
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs native core)

FIND_PACKAGE(BISON REQUIRED)
bison_target(BisonOutput ${oc_SOURCE_DIR}/parser.y ${oc_SOURCE_DIR}/parser.cc COMPILE_FLAGS "-d")

FIND_PACKAGE(FLEX REQUIRED)
flex_target(FlexOutput ${oc_SOURCE_DIR}/lexer.l ${oc_SOURCE_DIR}/lexer.cc)

include_directories(include/oc)

add_executable(oc ${oc_SOURCE_DIR}/main.cc ${oc_SOURCE_DIR}/AST.cc ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS})
